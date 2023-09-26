#ifndef __LENET_FORWARD_H__
#define __LENET_FORWARD_H__

#include <stdlib.h>
#include "lenet.h"
#include "cnnapi.h"
#include "utils.h"


void lenet_forward(LeNet5 *lenet, Feature *features);


#endif