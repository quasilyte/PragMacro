#include "lang/runtime/eval.h"

#include "lang/runtime/env/frame.h"
#include "lang/runtime/env/pc.h"
#include "lang/runtime/array.h"
#include "lang/runtime/object.h"

void handle_addi(FrameSlot dst, i32 val) {
  frame_seti(dst, frame_geti(dst) + val);
}

void handle_addl(FrameSlot dst, FrameSlot src) {
  frame_seti(dst, frame_geti(dst) + frame_geti(src));
}

void handle_subi(FrameSlot dst, i32 val) {
  frame_seti(dst, frame_geti(dst) - val);
}

void handle_subl(FrameSlot dst, FrameSlot src) {
  frame_seti(dst, frame_geti(dst) - frame_geti(src));
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

void handle_qloadi(FrameSlot dst, FrameSlot src, u8 idx) {
  frame_seti(dst, obj_qload(frame_geto(src), idx));
}

void handle_qloadl(FrameSlot dst, FrameSlot src, FrameSlot idx) {
  frame_seti(dst, obj_qload(frame_geto(src), frame_geti(idx)));
}

void handle_qstoreii(FrameSlot dst, u8 idx, i64 val) {
  obj_store(frame_geto(dst), idx, val);
}

void handle_qstoreil(FrameSlot dst, u8 idx, FrameSlot src) {
  obj_store(frame_geto(dst), idx, frame_geti(src));
}

void handle_qstoreli(FrameSlot dst, FrameSlot idx, i64 val) {
  obj_store(frame_geto(dst), frame_geti(idx), val);
}

void handle_qstorell(FrameSlot dst, FrameSlot idx, FrameSlot src) {
  obj_store(frame_geto(dst), frame_geti(idx), frame_geti(src));
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
  #define HANDLER3(NAME, T1, T2, T3) \
    op_##NAME: { \
      T1 a = pc_fetch_##T1(); \
      T2 b = pc_fetch_##T2(); \
      T3 c = pc_fetch_##T3(); \
      handle_##NAME(a, b, c); \
      NEXT_OP; \
    }

  static const void* handlers[] = {
    &&op_end,

    &&op_addi,
    &&op_addl,

    &&op_subi,
    &&op_subl,

    &&op_movl,
    &&op_movi,

    &&op_jnz,

    &&op_qloadi,
    &&op_qloadl,

    &&op_qstoreii,
    &&op_qstoreil,
    &&op_qstoreli,
    &&op_qstorell,
  };

  NEXT_OP;

  op_end: return;
  HANDLER2(addi, byte, i32)
  HANDLER2(addl, byte, byte)
  HANDLER2(subi, byte, i32)
  HANDLER2(subl, byte, byte)
  HANDLER2(movi, byte, i64)
  HANDLER2(movl, byte, byte)
  HANDLER2(jnz, byte, i16)
  HANDLER3(qloadi, byte, byte, byte)
  HANDLER3(qloadl, byte, byte, byte)
  HANDLER3(qstoreii, byte, byte, i64)
  HANDLER3(qstoreil, byte, byte, byte)
  HANDLER3(qstoreli, byte, byte, i64)
  HANDLER3(qstorell, byte, byte, byte)
}
