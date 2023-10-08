#include <stdio.h>
#include "utils.h"


int load_quantized_model(LeNet5 *lenet, char filename[])
{
	FILE *fp = fopen(filename, "rb");
	if (!fp) return 0;
	fread(lenet, sizeof(LeNet5), 1, fp);
	fclose(fp);
	return 1;
}


int read_data(unsigned char(*data)[28][28], unsigned char label[], const int count, const char data_file[], const char label_file[])
{
    FILE *fp_image = fopen(data_file, "rb");
    FILE *fp_label = fopen(label_file, "rb");
    if (!fp_image||!fp_label) return 1;
	fseek(fp_image, 16, SEEK_SET);
	fseek(fp_label, 8, SEEK_SET);
	fread(data, sizeof(*data)*count, 1, fp_image);
	fread(label,count, 1, fp_label);
	fclose(fp_image);
	fclose(fp_label);
	return 0;
}

void print_quantized_model(LeNet5 *lenet, char filename[]){

	FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }

	fprintf(file, "weight0_1:\n");
    for (int i = 0; i < INPUT; i++) {
        for (int j = 0; j < LAYER1; j++) {
            for (int k = 0; k < LENGTH_KERNEL; k++) {
                for (int l = 0; l < LENGTH_KERNEL; l++) {
                    fprintf(file, "%d, ", lenet->weight0_1[i][j][k][l]);
                }
            }
            fprintf(file, "\n");
        }
		fprintf(file, "\n");
    }

	fprintf(file, "weight2_3:\n");
    for (int i = 0; i < LAYER2; i++) {
        for (int j = 0; j < LAYER3; j++) {
            for (int k = 0; k < LENGTH_KERNEL; k++) {
                for (int l = 0; l < LENGTH_KERNEL; l++) {
                    fprintf(file, "%d, ", lenet->weight2_3[i][j][k][l]);
                }
            }
            fprintf(file, "\n");
        }
		fprintf(file, "\n");
    }

	fprintf(file, "weight4_5:\n");
    for (int i = 0; i < LAYER4; i++) {
        for (int j = 0; j < LAYER5; j++) {
            for (int k = 0; k < LENGTH_KERNEL; k++) {
                for (int l = 0; l < LENGTH_KERNEL; l++) {
                    fprintf(file, "%d, ", lenet->weight4_5[i][j][k][l]);
                }  
            }
            fprintf(file, "\n");
        }
		fprintf(file, "\n");
    }

	fprintf(file, "\n");
	fprintf(file, "weight5_6:\n");
    for (int i = 0; i < LAYER5 * LENGTH_FEATURE5 * LENGTH_FEATURE5; i++) {
        for (int j = 0; j < OUTPUT; j++) { 
            fprintf(file, "%d, ", lenet->weight5_6[i][j]); 
        }
		fprintf(file, "\n");
    }

    fprintf(file, "\n");
	fprintf(file, "bias0_1:\n");
    for (int i = 0; i < 6; i++) {
        fprintf(file, "%f, ", lenet->bias0_1[i]); 
    }
	fprintf(file, "\n");

    fprintf(file, "\n");
	fprintf(file, "bias2_3:\n");
    for (int i = 0; i < 16; i++) {
        fprintf(file, "%f, ", lenet->bias2_3[i]); 
    }
	fprintf(file, "\n");

    fprintf(file, "\n");
	fprintf(file, "bias4_5:\n");
    for (int i = 0; i < 120; i++) {
        fprintf(file, "%f, ", lenet->bias4_5[i]); 
    }
	fprintf(file, "\n");

    fprintf(file, "\n");
	fprintf(file, "bias5_6:\n");
    for (int i = 0; i < 10; i++) {
        fprintf(file, "%f, ", lenet->bias5_6[i]); 
    }
	fprintf(file, "\n");

    fprintf(file, "\n");
	fprintf(file, "c1_scale:\n");
    fprintf(file, "%f ", lenet->c1_scale);
	fprintf(file, "\n");

    fprintf(file, "\n");
	fprintf(file, "c2_scale:\n");
    fprintf(file, "%f ", lenet->c2_scale); 
	fprintf(file, "\n");

    fprintf(file, "\n");
	fprintf(file, "c3_scale:\n");
    fprintf(file, "%f ", lenet->c3_scale);
	fprintf(file, "\n");

    fprintf(file, "\n");
	fprintf(file, "fc_scale:\n");
    fprintf(file, "%f ", lenet->fc_scale); 
	fprintf(file, "\n");


	fclose(file);
}


