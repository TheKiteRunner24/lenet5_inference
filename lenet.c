#include <memory.h>
#include <time.h>
#include <stdlib.h>
#include "lenet.h"
#include "utils.h"
#include "lenet_forward.h"


static inline void load_input(Feature *features, image input)
{
	double (*layer0)[LENGTH_FEATURE0][LENGTH_FEATURE0] = features->input;
	const long sz = sizeof(image) / sizeof(**input);
	double mean = 0, std = 0;
	for(int j = 0; j < sizeof(image) / sizeof(*input); j++){
		for(int k = 0; k < sizeof(*input) / sizeof(**input); k++){
			mean += input[j][k];
			std += input[j][k] * input[j][k];
		}
		
	}
	mean /= sz;
	std = sqrt(std / sz - mean*mean);
	for(int j = 0; j < sizeof(image) / sizeof(*input); j++){
		for(int k = 0; k < sizeof(*input) / sizeof(**input); k++){
			layer0[0][j + PADDING][k + PADDING] = (input[j][k] - mean) / std;
		}
	}
}


static uint8_t get_result(Feature *features, uint8_t count)
{
	double *output = (double *)features->output_f; 
	uint8_t result = 0;
	double maxvalue = *output;
	for (uint8_t i = 1; i < count; ++i)
	{
		if (output[i] > maxvalue)
		{
			maxvalue = output[i];
			result = i;
		}
	}
	return result;
}


uint8_t Predict(LeNet5 *lenet, image input, uint8_t count)
{
	Feature features = { 0 };
	load_input(&features, input);
	lenet_forward(lenet, &features);
	return get_result(&features, count);
}
