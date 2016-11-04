#include "lang/runtime/env/pc.h"

#include "cstd/stdlib.h"

static const byte* pc_top;
static const byte* pc_ptr;

void pc_init(const byte* code) {
  pc_top = code;
  pc_ptr = code;
}

void pc_jump_rel(i16 offset) {
  pc_ptr += offset;
}

void pc_jump_abs(u64 offset) {
  pc_ptr = pc_top + offset;
}

u64 pc_offset(void) {
  return pc_ptr - pc_top;
}

byte pc_fetch_byte(void) {
  return *pc_ptr++;
}

#define GEN_FETCH(T) \
  T pc_fetch_##T(void) { \
    T result = *(T*)pc_ptr; \
    pc_ptr += sizeof(T); \
    return result; \
  }

GEN_FETCH(i16)
GEN_FETCH(i32)
GEN_FETCH(i64)
GEN_FETCH(u32)
