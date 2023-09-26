#ifndef __CNNAPI_H__
#define __CNNAPI_H__

#include "lenet.h"
#include "normal_instr.h"

void convolution(const int8_t* input, int input_size,
                        const int8_t* kernel, int kernel_size,
                        int32_t* output);

void fully_connected(const int8_t* input, const int8_t* weights, 
                    int num_left, int num_right, 
                    int32_t* output);

#endif