#include "lang/runtime/eval.h"

#include "lang/repr/opcode.h"
#include "lang/runtime/env/frame.h"
#include "lang/runtime/env/pc.h"
#include "lang/runtime/env/rtti.h"
#include "lang/runtime/types/array.h"
#include "lang/runtime/types/object.h"
#include "lang/symbol/func.h"

void handle_add_li(FrameSlot dst, i32 val) {
  frame_seti(dst, frame_geti(dst) + val);
}

void handle_add_ll(FrameSlot dst, FrameSlot src) {
  frame_seti(dst, frame_geti(dst) + frame_geti(src));
}

void handle_sub_li(FrameSlot dst, i32 val) {
  frame_seti(dst, frame_geti(dst) - val);
}

void handle_sub_ll(FrameSlot dst, FrameSlot src) {
  frame_seti(dst, frame_geti(dst) - frame_geti(src));
}

void handle_mov_li(FrameSlot dst, i64 val) {
  frame_seti(dst, val);
}

void handle_mov_ll(FrameSlot dst, FrameSlot src) {
  frame_seti(dst, frame_geti(src));
}

void handle_jnz(FrameSlot slot, i16 offset) {
  if (frame_geti(slot) != 0) {
    pc_jump_rel(offset);
  }
}

void handle_load_lli(FrameSlot dst, FrameSlot src, u8 idx) {
  frame_seti(dst, obj_load(frame_geto(src), idx));
}

void handle_load_lll(FrameSlot dst, FrameSlot src, FrameSlot idx) {
  frame_seti(dst, obj_load(frame_geto(src), frame_geti(idx)));
}

void handle_store_lii(FrameSlot dst, u8 idx, i64 val) {
  obj_store(frame_geto(dst), idx, val);
}

void handle_store_lil(FrameSlot dst, u8 idx, FrameSlot src) {
  obj_store(frame_geto(dst), idx, frame_geti(src));
}

void handle_store_lli(FrameSlot dst, FrameSlot idx, i64 val) {
  obj_store(frame_geto(dst), frame_geti(idx), val);
}

void handle_store_lll(FrameSlot dst, FrameSlot idx, FrameSlot src) {
  obj_store(frame_geto(dst), frame_geti(idx), frame_geti(src));
}

void handle_ret(void) {
  pc_jump_abs(frame_pop());
}

void handle_call_void(u32 func_id) {
  const Func* func = rtti_get_func(func_id);
  frame_push(func, pc_offset());
  pc_jump_abs(func->addr);
}

void eval(void) {
  #define NEXT_OP goto *handlers[pc_fetch_byte()]
  #define HANDLER0(NAME) \
    op_##NAME: { \
      handle_##NAME(); \
      NEXT_OP; \
    }
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
    [OP_END] = &&op_end,

    [OP_ADD_LI] = &&op_add_li,
    [OP_ADD_LL] = &&op_add_ll,

    [OP_SUB_LI] = &&op_sub_li,
    [OP_SUB_LL] = &&op_sub_ll,

    [OP_MOV_LI] = &&op_mov_li,
    [OP_MOV_LL] = &&op_mov_ll,

    [OP_JNZ] = &&op_jnz,

    [OP_LOAD_LLI] = &&op_load_lli,
    [OP_LOAD_LLL] = &&op_load_lll,

    [OP_STORE_LII] = &&op_store_lii,
    [OP_STORE_LIL] = &&op_store_lil,
    [OP_STORE_LLI] = &&op_store_lli,
    [OP_STORE_LLL] = &&op_store_lll,

    [OP_RET] = &&op_ret,
    [OP_CALL] = &&op_call,
  };

  NEXT_OP;

  op_end: return;
  HANDLER2(add_li, byte, i32)
  HANDLER2(add_ll, byte, byte)
  HANDLER2(sub_li, byte, i32)
  HANDLER2(sub_ll, byte, byte)
  HANDLER2(mov_li, byte, i64)
  HANDLER2(mov_ll, byte, byte)
  HANDLER2(jnz, byte, i16)
  HANDLER3(load_lli, byte, byte, byte)
  HANDLER3(load_lll, byte, byte, byte)
  HANDLER3(store_lii, byte, byte, i64)
  HANDLER3(store_lil, byte, byte, byte)
  HANDLER3(store_lli, byte, byte, i64)
  HANDLER3(store_lll, byte, byte, byte)
  HANDLER0(ret)
  HANDLER1(call_void, u32)
}

void eval_func(const Func* func) {
  frame_push(func, 0);
  pc_jump_abs(func->addr);
  eval();
}
