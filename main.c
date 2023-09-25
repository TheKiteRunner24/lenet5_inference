#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lenet.h"
#include "utils.h"


#define FILE_TRAIN_IMAGE		"train-images-idx3-ubyte"
#define FILE_TRAIN_LABEL		"train-labels-idx1-ubyte"
#define FILE_TEST_IMAGE		"t10k-images-idx3-ubyte"
#define FILE_TEST_LABEL		"t10k-labels-idx1-ubyte"
#define COUNT_TEST		100

int testing(LeNet5 *lenet, image *test_data, uint8_t *test_label,int total_size)
{
	int right = 0, percent = 0;
	for (int i = 0; i < total_size; ++i)
	{
		uint8_t l = test_label[i];
		int p = Predict(lenet, test_data[i], 10);
		right += l == p;
		if (i * 100 / total_size > percent)
			printf("test:%2d%%\n", percent = i * 100 / total_size);
	}
	return right;
}


void test(){
	image *test_data = (image *)calloc(COUNT_TEST, sizeof(image));
	uint8_t *test_label = (uint8_t *)calloc(COUNT_TEST, sizeof(uint8_t));
	if (read_data(test_data, test_label, COUNT_TEST, FILE_TEST_IMAGE, FILE_TEST_LABEL))
	{
		printf("ERROR!!!\nDataset File Not Find!Please Copy Dataset to the Folder Included the main.c\n");
		free(test_data);
		free(test_label);
	}

	LeNet5 *lenet = (LeNet5 *)malloc(sizeof(LeNet5));
	if(load_quantized_model(lenet, "quantized_model.dat") == 0){
		printf("load model fail\n");
	}

	clock_t start = clock();

	int right = testing(lenet, test_data, test_label, COUNT_TEST);

	printf("%d/%d\n", right, COUNT_TEST);
	printf("Time:%u\n", (unsigned)(clock() - start));

	free(lenet);
	free(test_data);
	free(test_label);
}



int main()
{

	test(); // 使用低精度模型进行推理
	
	return 0;
}
