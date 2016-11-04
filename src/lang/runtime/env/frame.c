#include "lang/runtime/env/frame.h"

#include "cstd/stdlib.h"

static const int SLOT_SIZE = sizeof(void*);

static byte* frame_top;
static const byte* frame_bottom;
static byte* frame_ptr;

void frame_init(u64 size) {
  assert(size >= 256 && "frame size is indecently low");

  frame_top = malloc(size);
  frame_bottom = frame_top + size;
  frame_ptr = frame_top;
}

void frame_set(FrameSlot slot, $Int val) {
  (($Int*)frame_ptr)[slot] = val;
}

$Int frame_get(FrameSlot slot) {
  return (($Int*)frame_ptr)[slot];
}

void frame_push(uint slot_count) {
  frame_ptr += slot_count * SLOT_SIZE;
  assert(frame_ptr <= frame_bottom && "frame overflow");
}

void frame_pop(uint slot_count) {
  frame_ptr -= slot_count * SLOT_SIZE;
  assert(frame_ptr >= frame_top && "frame underflow");
}
