#include "lang/runtime/pc.h"

#include "cstd/stddef.h"

static const byte* pc_ptr;

ProgramCounter* pc = NULL;

ProgramCounter* pc_excange(ProgramCounter* new_pc) {  
  ProgramCounter* old_pc = pc;
  if (old_pc) {
    old_pc->ptr = pc_ptr;
  }

  pc_ptr = new_pc->ptr;
  pc = new_pc;

  return old_pc;
}

void pc_jump(i16 offset) {
  pc_ptr += offset;
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
