#include "lang/runtime/eval.h"

#include "lang/runtime/env.h"
#include "lang/runtime/frame.h"

void handle_add1(Env* env) {
  FrameSlot dst = pc_byte(env);
  frame_set_int(dst, frame_get_int(dst) + 1);
}

void handle_addi(Env* env) {
  FrameSlot dst = pc_byte(env);
  i32 val = pc_i32(env);
  frame_set_int(dst, frame_get_int(dst) + val);
}

void handle_addl(Env* env) {
  FrameSlot dst = pc_byte(env);
  FrameSlot src = pc_byte(env);
  frame_set_int(dst, frame_get_int(dst) + frame_get_int(src));
}

void handle_mov0(Env* env) {
  FrameSlot dst = pc_byte(env);
  frame_set_int(dst, 0);
}

void handle_movi(Env* env) {
  FrameSlot dst = pc_byte(env);
  i64 val = pc_i64(env);
  frame_set_int(dst, val);
}

void handle_movl(Env* env) {
  FrameSlot dst = pc_byte(env);
  FrameSlot src = pc_byte(env);
  frame_set_int(dst, frame_get_int(src));
}

void handle_jnz(Env* env) {
  FrameSlot slot = pc_byte(env);
  i16 offset = pc_i16(env);
  if (frame_get_int(slot) != 0) {
    env->pc += offset;
  }
}

void eval(Env* env) {
  #define NEXT_OP goto *handlers[*env->pc++]
  #define HANDLER(NAME) op_##NAME: handle_##NAME(env); NEXT_OP

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
  HANDLER(add1);
  HANDLER(addi);
  HANDLER(addl);
  HANDLER(mov0);
  HANDLER(movl);
  HANDLER(movi);
  HANDLER(jnz);

  #undef NEXT_OP
  #undef HANDLER
}
