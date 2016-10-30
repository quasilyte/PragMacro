#include "lang/runtime/frame.h"

#include "cstd/stdlib.h"

static byte* fp_top;
static byte* fp_bottom;
static byte* fp;

static Frame* frame = NULL;

static const int SLOT_SIZE = sizeof(void*);

void frame_init(Frame* f, u64 byte_size) {
  f->top = malloc(byte_size);
  f->bottom = f->top + byte_size;
  f->ptr = f->top;
}

Frame* frame_exchange(Frame* new_frame) {
  fp_top = new_frame->top;
  fp_bottom = new_frame->bottom;
  fp = new_frame->ptr;

  Frame* old_frame = frame;
  frame = new_frame;
  return old_frame;
}

void frame_seti(FrameSlot slot, $int val) {
  (($int*)fp)[slot] = val;
}

void frame_setf(FrameSlot slot, $float val) {
  (($float*)fp)[slot] = val;
}

$int frame_geti(FrameSlot slot) {
  return (($int*)fp)[slot];
}

$float frame_getf(FrameSlot slot) {
  return (($float*)fp)[slot];
}

void frame_alloc(uint slot_count) {
  fp += slot_count * SLOT_SIZE;
  assert(fp <= fp_bottom && "frame overflow");
}

void frame_dealloc(uint slot_count) {
  fp -= slot_count * SLOT_SIZE;
  assert(fp >= fp_top && "frame underflow");
}
