#include "lang/runtime/env/frame.h"

#include "cstd/stdlib.h"

#include "lang/symbol/func.h"
#include "lang/runtime/env/rtti.h"

static byte* frame_top;
static const byte* frame_bottom;
static byte* frame_ptr;
static CallInfo* call_stack;

void frame_init(u64 size) {
  assert(size >= 256 && "frame size is indecently low");

  frame_top = malloc(size);
  frame_bottom = frame_top + size;
  frame_ptr = frame_top;

  call_stack = (CallInfo*)(frame_bottom - sizeof(CallInfo));
  call_stack->func = rtti_get_func(0);
  call_stack->ret_addr = 0;
}

void frame_set(FrameSlot slot, $Int val) {
  (($Int*)frame_ptr)[slot] = val;
}

$Int frame_get(FrameSlot slot) {
  return (($Int*)frame_ptr)[slot];
}

void frame_push(const Func* func, u64 ret_addr) {
  const CallInfo* cinfo = call_stack;
  call_stack -= 1;

  call_stack->func = func;
  call_stack->ret_addr = ret_addr;

  frame_ptr += cinfo->func->frame_size;
  assert(frame_ptr < (byte*)call_stack && "overflow");
}

u64 frame_pop(void) {
  call_stack += 1;
  frame_ptr -= call_stack->func->frame_size;
  assert(frame_ptr >= frame_top && "underflow");
  return (call_stack - 1)->ret_addr;
}
