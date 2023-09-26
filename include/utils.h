#ifndef __UTILS_H__
#define __UTILS_H__


#include "lenet.h"


int read_data(unsigned char(*data)[28][28], unsigned char label[], const int count, const char data_file[], const char label_file[]);

int load_quantized_model(LeNet5 *lenet, char filename[]);


#endif