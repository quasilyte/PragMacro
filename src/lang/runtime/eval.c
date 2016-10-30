#include "lang/runtime/eval.h"

#include "lang/runtime/frame.h"
#include "lang/runtime/pc.h"

void handle_add1(FrameSlot dst) {
  frame_seti(dst, frame_geti(dst) + 1);
}

void handle_addi(FrameSlot dst, i32 val) {
  frame_seti(dst, frame_geti(dst) + val);
}

void handle_addl(FrameSlot dst, FrameSlot src) {
  frame_seti(dst, frame_geti(dst) + frame_geti(src));
}

void handle_sub1(FrameSlot dst) {
  frame_seti(dst, frame_geti(dst) - 1);
}

void handle_subi(FrameSlot dst, i32 val) {
  frame_seti(dst, frame_geti(dst) - val);
}

void handle_subl(FrameSlot dst, FrameSlot src) {
  frame_seti(dst, frame_geti(dst) - frame_geti(src));
}

void handle_mov0(FrameSlot dst) {
  frame_seti(dst, 0);
}

void handle_movi(FrameSlot dst, i64 val) {
  frame_seti(dst, val);
}

void handle_movl(FrameSlot dst, FrameSlot src) {
  frame_seti(dst, frame_geti(src));
}

void handle_jnz(FrameSlot slot, i16 offset) {
  if (frame_geti(slot) != 0) {
    pc_jump(offset);
  }
}

void eval(void) {
  #define NEXT_OP goto *handlers[pc_fetch_byte()]
  #define HANDLER1(NAME, T1) \
    op_##NAME: { \
      T1 a = pc_fetch_##T1(); \
      handle_##NAME(a); \
      NEXT_OP; \
    }
  #define HANDLER2(NAME, T1, T2) \
    op_##NAME: { \
      T1 a = pc_fetch_##T1(); \
      T2 b = pc_fetch_##T2(); \
      handle_##NAME(a, b); \
      NEXT_OP; \
    }

  static const void* handlers[] = {
    &&op_end,

    &&op_add1,
    &&op_addi,
    &&op_addl,

    &&op_sub1,
    &&op_subi,
    &&op_subl,

    &&op_mov0,
    &&op_movl,
    &&op_movi,

    &&op_jnz,
  };

  NEXT_OP;

  op_end: return;
  HANDLER1(add1, byte)
  HANDLER2(addi, byte, i32)
  HANDLER2(addl, byte, byte)
  HANDLER1(sub1, byte)
  HANDLER2(subi, byte, i32)
  HANDLER2(subl, byte, byte)
  HANDLER1(mov0, byte)
  HANDLER2(movi, byte, i64)
  HANDLER2(movl, byte, byte)
  HANDLER2(jnz, byte, i16)
}
