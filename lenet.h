#ifndef __LENET_H__
#define __LENET_H__

#include <stdint.h>

#define LENGTH_KERNEL	5

#define LENGTH_FEATURE0	32
#define LENGTH_FEATURE1	(LENGTH_FEATURE0 - LENGTH_KERNEL + 1)
#define LENGTH_FEATURE2	(LENGTH_FEATURE1 >> 1)
#define LENGTH_FEATURE3	(LENGTH_FEATURE2 - LENGTH_KERNEL + 1)
#define	LENGTH_FEATURE4	(LENGTH_FEATURE3 >> 1)
#define LENGTH_FEATURE5	(LENGTH_FEATURE4 - LENGTH_KERNEL + 1)

#define INPUT			1
#define LAYER1			6
#define LAYER2			6
#define LAYER3			16
#define LAYER4			16
#define LAYER5			120
#define OUTPUT          10

#define PADDING 2


typedef uint8_t image[28][28];


typedef struct LeNet5
{
	int8_t weight0_1[INPUT][LAYER1][LENGTH_KERNEL][LENGTH_KERNEL];
	int8_t weight2_3[LAYER2][LAYER3][LENGTH_KERNEL][LENGTH_KERNEL];
	int8_t weight4_5[LAYER4][LAYER5][LENGTH_KERNEL][LENGTH_KERNEL];
	int8_t weight5_6[LAYER5 * LENGTH_FEATURE5 * LENGTH_FEATURE5][OUTPUT];

	double bias0_1[LAYER1];
	double bias2_3[LAYER3];
	double bias4_5[LAYER5];
	double bias5_6[OUTPUT];

	double c1_scale;
	double c2_scale;
	double c3_scale;
	double fc_scale;

}LeNet5;

typedef struct Feature
{
	double input[INPUT][LENGTH_FEATURE0][LENGTH_FEATURE0];
	int8_t input_q[INPUT][LENGTH_FEATURE0][LENGTH_FEATURE0];

	//卷积
	int32_t layer1[LAYER1][LENGTH_FEATURE1][LENGTH_FEATURE1];
	double layer1_f[LAYER1][LENGTH_FEATURE1][LENGTH_FEATURE1];
	int8_t layer1_q[LAYER1][LENGTH_FEATURE1][LENGTH_FEATURE1];

	//池化
	int8_t layer2[LAYER2][LENGTH_FEATURE2][LENGTH_FEATURE2];

	//卷积
	int32_t layer3[LAYER3][LENGTH_FEATURE3][LENGTH_FEATURE3];
	double layer3_f[LAYER3][LENGTH_FEATURE3][LENGTH_FEATURE3];
	int8_t layer3_q[LAYER3][LENGTH_FEATURE3][LENGTH_FEATURE3];

	//池化
	int8_t layer4[LAYER4][LENGTH_FEATURE4][LENGTH_FEATURE4];

	//卷积
	int32_t layer5[LAYER5][LENGTH_FEATURE5][LENGTH_FEATURE5];
	double layer5_f[LAYER5][LENGTH_FEATURE5][LENGTH_FEATURE5];
	int8_t layer5_q[LAYER5][LENGTH_FEATURE5][LENGTH_FEATURE5];

	//全连接
	int32_t output[OUTPUT];
	double output_f[OUTPUT];

}Feature;

uint8_t Predict(LeNet5 *lenet, image input, uint8_t count);

#endif
