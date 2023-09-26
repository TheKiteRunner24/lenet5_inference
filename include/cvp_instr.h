#ifndef __CVP_INSTR_H__
#define __CVP_INSTR_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int32_t Conv(int64_t src, int64_t ker, int32_t last, int sew);

int16_t Pool_Max(int64_t src, int16_t last, int sew);
int32_t Pool_Avg(int64_t src, int32_t last, int sew);

int16_t Pool_M_Max(int64_t src, int sew);
int16_t Pool_M_Avg(int64_t src, int sew);

int64_t Act_Relu(int64_t src, int64_t zero, int sew);
int64_t Act_Relu6(int64_t src, int64_t zero, int sew);

int64_t Add_N(int64_t src_a, int64_t src_b, int64_t zero, int sew);
int64_t Add_Relu(int64_t src_a, int64_t src_b, int64_t zero, int sew);

#ifdef __cplusplus
}
#endif

#endif