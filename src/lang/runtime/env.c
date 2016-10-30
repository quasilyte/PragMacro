#include "lang/runtime/env.h"

byte pc_byte(Env* env) {
  return *env->pc++;
}

#define GEN_IX(X) \
  X pc_##X(Env* env) { \
    X x = *(X*)env->pc; \
    env->pc += sizeof(X); \
    return x; \
  }

GEN_IX(i16)
GEN_IX(i32)
GEN_IX(i64)
