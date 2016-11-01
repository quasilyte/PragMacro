#include "lang/runtime/env/frame.h"

#include "cstd/stdlib.h"

STRUCT(Frame) {
  byte* top;
  byte* bottom;
  byte* ptr;
};

static const int SLOT_SIZE = sizeof(void*);

static byte* frame_top;
static const byte* frame_bottom;
static byte* frame_ptr;

static Frame* current_frame = NULL;

Frame* new_frame(u64 size) {
  assert(size >= 256 && "frame size is indecently low");

  Frame* f = malloc(sizeof(Frame));

  f->top = malloc(size);
  f->bottom = f->top + size;
  f->ptr = f->top;

  return f;
}

void delete_frame(Frame* f) {
  free(f->top);
  free(f);
}

Frame* frame_exchange(Frame* new_f) {
  Frame* old_f = current_frame;
  if (old_f) {
    old_f->ptr = frame_ptr;
  }

  frame_top = new_f->top;
  frame_bottom = new_f->bottom;
  frame_ptr = new_f->ptr;

  current_frame = new_f;

  return old_f;
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

$Object* frame_geto(FrameSlot slot) {
  return ($Object*)frame_geti(slot);
}

$Float frame_getf(FrameSlot slot) {
  return (($Float*)frame_ptr)[slot];
}

void frame_push(uint slot_count) {
  frame_ptr += slot_count * SLOT_SIZE;
  assert(frame_ptr <= frame_bottom && "frame overflow");
}

void frame_pop(uint slot_count) {
  frame_ptr -= slot_count * SLOT_SIZE;
  assert(frame_ptr >= frame_top && "frame underflow");
}
