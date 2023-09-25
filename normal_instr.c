#include "normal_instr.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

int32_t Conv(int64_t src, int64_t ker, int32_t last, int sew) {

    int32_t result = last;

    for (int i = 0; i < 8; i++) {
        int8_t srcData = (src >> (i * 8)) & 0xFF;
        int8_t kerData = (ker >> (i * 8)) & 0xFF;
        
        result += srcData * kerData;
    }
    return result;
}



#ifdef __cplusplus
}
#endif