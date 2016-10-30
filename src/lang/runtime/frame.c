#include "lang/runtime/frame.h"

#include "cstd/stdlib.h"

static const int SLOT_SIZE = sizeof(void*);

static byte* frame_top;
static byte* frame_bottom;
static byte* frame_ptr;

static Frame* frame = NULL;

void frame_init(Frame* f, u64 byte_size) {
  f->top = malloc(byte_size);
  f->bottom = f->top + byte_size;
  f->ptr = f->top;
}

Frame* frame_exchange(Frame* new_frame) {
  Frame* old_frame = frame;
  if (old_frame) {
    old_frame->ptr = frame_ptr;
  }

  frame_top = new_frame->top;
  frame_bottom = new_frame->bottom;
  frame_ptr = new_frame->ptr;

  frame = new_frame;
  return old_frame;
}

void frame_seti(FrameSlot slot, $Int val) {
  (($Int*)frame_ptr)[slot] = val;
}

void frame_setf(FrameSlot slot, $Float val) {
  (($Float*)frame_ptr)[slot] = val;
}

$Int frame_geti(FrameSlot slot) {
  return (($Int*)frame_ptr)[slot];
}

$Float frame_getf(FrameSlot slot) {
  return (($Float*)frame_ptr)[slot];
}

void frame_alloc(uint slot_count) {
  frame_ptr += slot_count * SLOT_SIZE;
  assert(frame_ptr <= frame_bottom && "frame overflow");
}

void frame_dealloc(uint slot_count) {
  frame_ptr -= slot_count * SLOT_SIZE;
  assert(frame_ptr >= frame_top && "frame underflow");
}
