#include <stdlib.h>
#include <math.h>
#include "lenet_forward.h"


int8_t ReLU(int8_t x)
{
	if(x < 0){
        return 0;
    }
    else{
        return x;
    }
}


void prepare_conv_data(const int8_t* input, int inputRows, int inputCols,
                         int kernelRows, int kernelCols,
                         int8_t* input_prepared){

    int outputRows = inputRows - kernelRows + 1;
    int outputCols = inputCols - kernelCols + 1;

    int idx = 0;
    for (int i = 0; i < outputRows; i++) {
        for (int j = 0; j < outputCols; j++) {
            for (int m = 0; m < kernelRows; m++) {
                for (int n = 0; n < kernelCols; n++) {
                    input_prepared[idx++] = input[(i + m) * inputCols + (j + n)]; 
                }
            }
        }
    }
}

double quantize(double* input, int len, int8_t* output){

    double min = input[0];
    double max = input[0];

    for(int i = 0; i < len; i++){
        if(input[i] < min){
            min = input[i];
        }   
        if(input[i] > max){
            max = input[i];
        }
    }

    double absmax = fabs(max) > fabs(min) ? fabs(max) : fabs(min);
    double scale = absmax / 127;

    for(int i = 0; i < len; i++){
        output[i] = (int8_t)(input[i] / scale);
    }

    return scale;
}

void lenet_forward(LeNet5 *lenet, Feature *features)
{
    // 量化输入图像到int8
    double* inf = (double*)features->input;
    int8_t* inq = (int8_t*)features->input_q;
    double in_scale = quantize(inf, 6*32*32, inq);

	// 卷积层1 ============================================================================================

	for (int x = 0; x < 1; ++x) {  //1个图像
		for (int y = 0; y < 6; ++y) {  //6个卷积核

			int8_t* input = (int8_t*)features->input_q[x];
			int8_t* kernel = (int8_t*)lenet->weight0_1[x][y];
			int32_t* output = (int32_t*)features->layer1[y];
			
			//输入图像加了padding变成32*32
			int input_size = (32-5+1) * (32-5+1) * 25;
            int kernel_size = 25;

			int8_t* input_prepared= (int8_t*)calloc(input_size, sizeof(int8_t));

			prepare_conv_data(input, 32, 32, 5, 5, input_prepared);
			convolution(input_prepared, input_size, kernel, kernel_size, output);

			free(input_prepared);
		}
	}

    // int32的结果反量化到double，然后和double类型的bias相加
    // r = q * S
    for (int j = 0; j < 6; ++j) {
		for (int i = 0; i < 784; ++i) {
			((double *)features->layer1_f[j])[i] = ((int32_t *)features->layer1[j])[i] * lenet->c1_scale * in_scale;
		}
	}

    // 加偏置
    for (int j = 0; j < 6; ++j) {
		for (int i = 0; i < 784; ++i) {
			((double *)features->layer1_f[j])[i] += lenet->bias0_1[j];
		}
	}

    // double再次量化到int8，作为后续输入
    double* l1f = (double*)features->layer1_f;
    int8_t* l1q = (int8_t*)features->layer1_q;
    double l1_scale = quantize(l1f, 6*784, l1q);
    
    // 激活，使用int8
    for (int j = 0; j < 6; ++j) {
		for (int i = 0; i < 784; ++i) {
			((int8_t *)features->layer1_q[j])[i] = ReLU(((int8_t *)features->layer1_q[j])[i]);
		}
	}


	// 池化层2 ============================================================================================

    int pool_size = 2;

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 14; ++j) {
            for (int k = 0; k < 14; ++k) {
                int inputRow = j * 2;
                int inputCol = k * 2;
                int8_t maxVal = features->layer1_q[i][inputRow][inputCol];
                for (int m = 0; m < pool_size; m++) {
                    for (int n = 0; n < pool_size; n++) {
                        int8_t currentVal = features->layer1_q[i][inputRow + m][inputCol + n];
                        if (currentVal > maxVal) {
                            maxVal = currentVal;
                        }
                    }
                }
                features->layer2[i][j][k] = maxVal;
            }
        }
    }

    // 卷积层3 ============================================================================================
    // 6 * 14 * 14 => 6 * 10 * 10

    for (int x = 0; x < 6; ++x) {  //6个图像
		for (int y = 0; y < 16; ++y) {  //16个卷积核

			int8_t* input = (int8_t*)features->layer2[x];
			int8_t* kernel = (int8_t*)lenet->weight2_3[x][y];
			int32_t* output = (int32_t*)features->layer3[y];
			
			int kernel_size = 25;
			int input_size = (14-5+1) * (14-5+1) * 25;

			int8_t* input_prepared= (int8_t*)calloc(input_size, sizeof(int8_t));

			prepare_conv_data(input, 14, 14, 5, 5, input_prepared);
			convolution(input_prepared, input_size, kernel, kernel_size, output);

			free(input_prepared);
		}
	}

    // int32的结果反量化到double，然后和double类型的bias相加
    for (int j = 0; j < 16; ++j) {
		for (int i = 0; i < 100; ++i) {
			((double *)features->layer3_f[j])[i] = ((int32_t *)features->layer3[j])[i] * lenet->c2_scale * l1_scale;
		}
	}

    // 加偏置
    for (int j = 0; j < 16; ++j) {
		for (int i = 0; i < 100; ++i) {
			((double *)features->layer3_f[j])[i] += lenet->bias2_3[j];
		}
	}

    // double再次量化到int8，作为后续输入
    double* l3f = (double*)features->layer3_f;
    int8_t* l3q = (int8_t*)features->layer3_q;
    double l3_scale = quantize(l3f, 16*100, l3q);
    
    // 激活，使用int8
    for (int j = 0; j < 16; ++j) {
		for (int i = 0; i < 100; ++i) {
			((int8_t *)features->layer3_q[j])[i] = ReLU(((int8_t *)features->layer3_q[j])[i]);
		}
	}

    // 池化层4 ============================================================================================

    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 5; ++j) {
            for (int k = 0; k < 5; ++k) {
                int inputRow = j * 2;
                int inputCol = k * 2;
                int8_t maxVal = features->layer3_q[i][inputRow][inputCol];
                for (int m = 0; m < pool_size; m++) {
                    for (int n = 0; n < pool_size; n++) {
                        int8_t currentVal = features->layer3_q[i][inputRow + m][inputCol + n];
                        if (currentVal > maxVal) {
                            maxVal = currentVal;
                        }
                    }
                }
                features->layer4[i][j][k] = maxVal;
            }
        }
    }
    
    
    // 卷积层5 =====================================================================================================
    
    for (int x = 0; x < 16; ++x) {
        for (int y = 0; y < 120; ++y) {
            int8_t* input = (int8_t*)features->layer4[x];
			int8_t* kernel = (int8_t*)lenet->weight4_5[x][y];
			int32_t* output = (int32_t*)features->layer5[y];

			int kernel_size = 25;
			int input_size = 25;

            convolution(input, input_size, kernel, kernel_size, output);
        }
    }

    // int32的结果反量化到double，然后和double类型的bias相加
    for (int i = 0; i < 120; ++i) {
        ((double *)features->layer5_f[i])[0] = ((int32_t *)features->layer5[i])[0] * lenet->c3_scale * l3_scale;
    }

    // 加偏置
    for (int i = 0; i < 120; ++i) {
        ((double *)features->layer5_f[i])[0] += lenet->bias4_5[i];
    }

    // double再次量化到int8，作为后续输入
    double* l5f = (double*)features->layer5_f;
    int8_t* l5q = (int8_t*)features->layer5_q;
    double l5_scale = quantize(l5f, 120, l5q);
	
    // 激活，使用int8
    for (int i = 0; i < 120; ++i) {
        ((int8_t *)features->layer5_q[i])[0] = ReLU(((int8_t *)features->layer5_q[i])[0]);
    }

    
    // 全连接层 =====================================================================================================================================
    
    int8_t* input = (int8_t*)features->layer5_q;
    int8_t* weights = (int8_t*)lenet->weight5_6;
    int32_t* output = (int32_t*)features->output;

    fully_connected(input, weights, 120, 10, output); 

    // int32的结果反量化到double，然后和double类型的bias相加
    for (int i = 0; i < 10; ++i) {
        features->output_f[i] = features->output[i] * lenet->fc_scale * l5_scale;
    }

    // 加偏置
    for (int i = 0; i < 10; ++i) {
        features->output_f[i] += lenet->bias5_6[i];
    }

    // 激活
    for (int i = 0; i < 10; ++i) {
        features->output_f[i] = features->output_f[i] > 0.0 ? features->output_f[i] : 0.0;
    }
}

