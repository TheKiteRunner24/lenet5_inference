#ifndef __CNNAPI_BASE_H__
#define __CNNAPI_BASE_H__

#include "lenet.h"

#pragma once

void convolution_valid(const int8* input, int input_size,
                        const int8* kernel, int kernel_size,
                        int32* output);

void fully_connected(const int8* input, const int8* weights, 
                    int num_left, int num_right, 
                    int32* output);

#endif