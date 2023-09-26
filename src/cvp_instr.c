#include "cvp_instr.h"

#ifdef __cplusplus
extern "C" {
#endif

inline int32_t Conv(int64_t src, int64_t ker, int32_t last, int sew) {
  register int64_t src_reg __asm__ ("a0") = src;
  register int64_t ker_reg __asm__ ("a1") = ker;
  register int32_t last_reg __asm__ ("a2") = last;
  register int32_t res __asm__ ("a2");

  switch (sew) {
    case 0: {
      __asm__ volatile(
        ".word 0x00b5060b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg), [ker_reg]"r"(ker_reg), [last_reg]"0"(last_reg)
      );
      break;
    }
    case 1: {
      __asm__ volatile(
        ".word 0x02b5060b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg), [ker_reg]"r"(ker_reg), [last_reg]"0"(last_reg)
      );
      break;
    }
    case 2: {
      __asm__ volatile(
        ".word 0x04b5060b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg), [ker_reg]"r"(ker_reg), [last_reg]"0"(last_reg)
      );
      break;
    }
    default: {  // case 3
      __asm__ volatile(
        ".word 0x06b5060b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg), [ker_reg]"r"(ker_reg), [last_reg]"0"(last_reg)
      );
      break;
    }
  }
  return res;
}

inline int16_t Pool_Max(int64_t src, int16_t last, int sew) {
  register int64_t src_reg __asm__ ("a0") = src;
  register int16_t last_reg __asm__ ("a1") = last;
  register int16_t res __asm__ ("a1");

  switch (sew) {
    case 0: {
      __asm__ volatile(
        ".word 0x0015258b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg), [last_reg]"0"(last_reg)
      );
      break;
    }
    case 1: {
      __asm__ volatile(
        ".word 0x0215258b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg), [last_reg]"0"(last_reg)
      );
      break;
    }
    case 2: {
      __asm__ volatile(
        ".word 0x0415258b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg), [last_reg]"0"(last_reg)
      );
      break;
    }
    default: {  // case 3
      __asm__ volatile(
        ".word 0x0615258b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg), [last_reg]"0"(last_reg)
      );
      break;
    }
  }
  return res;
}

inline int32_t Pool_Avg(int64_t src, int32_t last, int sew) {
  register int64_t src_reg __asm__ ("a0") = src;
  register int32_t last_reg __asm__ ("a1") = last;
  register int32_t res __asm__ ("a1");

  switch (sew) {
    case 0: {
      __asm__ volatile(
        ".word 0x0025258b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg), [last_reg]"0"(last_reg)
      );
      break;
    }
    case 1: {
      __asm__ volatile(
        ".word 0x0225258b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg), [last_reg]"0"(last_reg)
      );
      break;
    }
    case 2: {
      __asm__ volatile(
        ".word 0x0425258b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg), [last_reg]"0"(last_reg)
      );
      break;
    }
    default: {  // case 3
      __asm__ volatile(
        ".word 0x0625258b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg), [last_reg]"0"(last_reg)
      );
      break;
    }
  }
  return res;
}

inline int16_t Pool_M_Max(int64_t src, int sew) {
  register int64_t src_reg __asm__ ("a0") = src;
  register int16_t res __asm__ ("a1");

  switch (sew) {
    case 0: {
      __asm__ volatile(
        ".word 0x2015358b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg)
      );
      break;
    }
    case 1: {
      __asm__ volatile(
        ".word 0x2215358b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg)
      );
      break;
    }
    case 2: {
      __asm__ volatile(
        ".word 0x2415358b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg)
      );
      break;
    }
    default: {  // case 3
      __asm__ volatile(
        ".word 0x2615358b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg)
      );
      break;
    }
  }
  return res;
}

inline int16_t Pool_M_Avg(int64_t src, int sew) {
  register int64_t src_reg __asm__ ("a0") = src;
  register int16_t res __asm__ ("a1");

  switch (sew) {
    case 0: {
      __asm__ volatile(
        ".word 0x2025358b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg)
      );
      break;
    }
    case 1: {
      __asm__ volatile(
        ".word 0x2225358b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg)
      );
      break;
    }
    case 2: {
      __asm__ volatile(
        ".word 0x2425358b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg)
      );
      break;
    }
    default: {  // case 3
      __asm__ volatile(
        ".word 0x2625358b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg)
      );
      break;
    }
  }
  return res;
}

inline int64_t Act_Relu(int64_t src, int64_t zero, int sew) {
  register int64_t src_reg  __asm__ ("a0") = src;
  register int64_t zero_reg __asm__ ("a1") = zero;
  register int64_t res __asm__ ("a2");

  switch (sew) {
    case 0: {
      __asm__ volatile(
        ".word 0x00b5460b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg), [zero_reg]"r"(zero_reg)
      );
      break;
    }
    case 1: {
      __asm__ volatile(
        ".word 0x02b5460b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg), [zero_reg]"r"(zero_reg)
      );
      break;
    }
    case 2: {
      __asm__ volatile(
        ".word 0x04b5460b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg), [zero_reg]"r"(zero_reg)
      );
      break;
    }
    default: {  // case 3
      __asm__ volatile(
        ".word 0x06b5460b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg), [zero_reg]"r"(zero_reg)
      );
      break;
    }
  }
  return res;
}

inline int64_t Act_Relu6(int64_t src, int64_t zero, int sew) {
  register int64_t src_reg  __asm__ ("a0") = src;
  register int64_t zero_reg __asm__ ("a1") = zero;
  register int64_t res __asm__ ("a2");

  switch (sew) {
    case 0: {
      __asm__ volatile(
        ".word 0x10b5460b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg), [zero_reg]"r"(zero_reg)
      );
      break;
    }
    case 1: {
      __asm__ volatile(
        ".word 0x12b5460b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg), [zero_reg]"r"(zero_reg)
      );
      break;
    }
    case 2: {
      __asm__ volatile(
        ".word 0x14b5460b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg), [zero_reg]"r"(zero_reg)
      );
      break;
    }
    default: {  // case 3
      __asm__ volatile(
        ".word 0x16b5460b"
        :[res]"=r"(res)
        :[src_reg]"r"(src_reg), [zero_reg]"r"(zero_reg)
      );
      break;
    }
  }
  return res;
}

inline int64_t Add_N(int64_t src_a, int64_t src_b, int64_t zero, int sew) {
  register int64_t src_a_reg __asm__ ("a0") = src_a;
  register int64_t src_b_reg __asm__ ("a1") = src_b;
  register int64_t zero_reg  __asm__ ("a3") = zero;
  register int64_t res __asm__ ("a2");

  switch (sew) {
    case 0: {
      __asm__ volatile(
        ".word 0x00b5560b"
        :[res]"=r"(res)
        :[src_a_reg]"r"(src_a_reg), [src_b_reg]"r"(src_b_reg), [zero_reg]"r"(zero_reg)
      );
      break;
    }
    case 1: {
      __asm__ volatile(
        ".word 0x02b5560b"
        :[res]"=r"(res)
        :[src_a_reg]"r"(src_a_reg), [src_b_reg]"r"(src_b_reg), [zero_reg]"r"(zero_reg)
      );
      break;
    }
    case 2: {
      __asm__ volatile(
        ".word 0x04b5560b"
        :[res]"=r"(res)
        :[src_a_reg]"r"(src_a_reg), [src_b_reg]"r"(src_b_reg), [zero_reg]"r"(zero_reg)
      );
      break;
    }
    default: {  // case 3
      __asm__ volatile(
        ".word 0x06b5560b"
        :[res]"=r"(res)
        :[src_a_reg]"r"(src_a_reg), [src_b_reg]"r"(src_b_reg), [zero_reg]"r"(zero_reg)
      );
      break;
    }
  }
  return res;
}

inline int64_t Add_Relu(int64_t src_a, int64_t src_b, int64_t zero, int sew) {
  register int64_t src_a_reg __asm__ ("a0") = src_a;
  register int64_t src_b_reg __asm__ ("a1") = src_b;
  register int64_t zero_reg  __asm__ ("a3") = zero;
  register int64_t res __asm__ ("a2");

  switch (sew) {
    case 0: {
      __asm__ volatile(
        ".word 0x10b5560b"
        :[res]"=r"(res)
        :[src_a_reg]"r"(src_a_reg), [src_b_reg]"r"(src_b_reg), [zero_reg]"r"(zero_reg)
      );
      break;
    }
    case 1: {
      __asm__ volatile(
        ".word 0x12b5560b"
        :[res]"=r"(res)
        :[src_a_reg]"r"(src_a_reg), [src_b_reg]"r"(src_b_reg), [zero_reg]"r"(zero_reg)
      );
      break;
    }
    case 2: {
      __asm__ volatile(
        ".word 0x14b5560b"
        :[res]"=r"(res)
        :[src_a_reg]"r"(src_a_reg), [src_b_reg]"r"(src_b_reg), [zero_reg]"r"(zero_reg)
      );
      break;
    }
    default: {  // case 3
      __asm__ volatile(
        ".word 0x16b5560b"
        :[res]"=r"(res)
        :[src_a_reg]"r"(src_a_reg), [src_b_reg]"r"(src_b_reg), [zero_reg]"r"(zero_reg)
      );
      break;
    }
  }
  return res;
}


#ifdef __cplusplus
}
#endif