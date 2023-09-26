#include "cnnapi.h"
#include <stdio.h>


// 生成单个5*5窗口的卷积数据
void gen_conv_data(const int8_t* data, int64_t result[4]){

    int dataIndex = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            if (dataIndex < 25) {
                int8_t signedData = data[dataIndex];
                int64_t zeroExtendedData = ((int64_t)signedData) & 0xFF;
                result[i] |= ((int64_t)zeroExtendedData) << (j * 8);
                dataIndex++;
            }
        }
    }
}


// 单个5*5窗口的卷积操作
int32_t conv_single(const int8_t* src, const int8_t* ker){

    //25个元素被放在4个int64里
    int64_t src_reg[4] = {0};
    gen_conv_data(src, src_reg);
    int64_t ker_reg[4] = {0};
    gen_conv_data(ker, ker_reg);

    int32_t temp = 0;
    for(int i = 0; i < 4; i++){
        temp = Conv(src_reg[i], ker_reg[i], temp, 2);
    }
    return temp;
}


void convolution(const int8_t* input, int input_size,
                        const int8_t* kernel, int kernel_size,
                        int32_t* output){

    int n_conv = input_size / kernel_size;

    for (int i = 0; i < n_conv; i++) {
        const int8_t *subInput = &input[i * kernel_size];
        output[i] += conv_single(subInput, kernel);
    }
}


void fully_connected(const int8_t* input, const int8_t* weights, 
                    int num_left, int num_right, 
                    int32_t* output){

    for (int i = 0; i < num_left * num_right; i++){
            output[i % num_right] += input[i / num_right] * weights[i];
    }
}