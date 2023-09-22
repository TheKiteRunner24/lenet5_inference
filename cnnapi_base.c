#include "cnnapi_base.h"

void convolution_valid(const int8* input, int input_size,
                        const int8* kernel, int kernel_size,
                        int32* output){

    int i = 0;
    while (i < input_size) {
        for (int j = 0; j < kernel_size; j++, i++) {
            output[i / kernel_size] += input[i] * kernel[j];
        }
    }
}

void fully_connected(const int8* input, const int8* weights, 
                    int num_left, int num_right, 
                    int32* output){

    for (int i = 0; i < num_left * num_right; i++){
            output[i % num_right] += input[i / num_right] * weights[i];
    }
}
