#include "lang/runtime/eval.h"

#include "lang/runtime/env.h"
#include "lang/runtime/frame.h"

void handle_add1(FrameSlot dst) {
  frame_seti(dst, frame_geti(dst) + 1);
}

void handle_addi(FrameSlot dst, i32 val) {
  frame_seti(dst, frame_geti(dst) + val);
}

void handle_addl(FrameSlot dst, FrameSlot src) {
  frame_seti(dst, frame_geti(dst) + frame_geti(src));
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

void handle_jnz(Env* env, FrameSlot slot, i16 offset) {
  if (frame_geti(slot) != 0) {
    env->pc += offset;
  }
}

void eval(Env* env) {
  #define NEXT_OP goto *handlers[*env->pc++]
  #define HANDLER(NAME) op_##NAME: handle_##NAME(env); NEXT_OP
  #define HANDLER1(NAME, T1) \
    op_##NAME: { \
      T1 a = pc_##T1(env); \
      handle_##NAME(a); \
      NEXT_OP; \
    }
  #define HANDLER2(NAME, T1, T2) \
    op_##NAME: { \
      T1 a = pc_##T1(env); \
      T2 b = pc_##T2(env); \
      handle_##NAME(a, b); \
      NEXT_OP; \
    }
  #define HANDLER2E(NAME, A, B) \
    op_##NAME: { \
      A a = pc_##A(env); \
      B b = pc_##B(env); \
      handle_##NAME(env, a, b); \
      NEXT_OP; \
    }

  static const void* handlers[] = {
    &&op_end,

    &&op_add1,
    &&op_addi,
    &&op_addl,

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
  HANDLER1(mov0, byte)
  HANDLER2(movi, byte, i64)
  HANDLER2(movl, byte, byte)
  HANDLER2E(jnz, byte, i16)
}
