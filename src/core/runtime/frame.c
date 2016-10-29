#include "core/runtime/frame.h"

#include "cstd/stdlib.h"

static byte* fp_top;
static byte* fp_bottom;
static byte* fp;

static const int SLOT_SIZE = sizeof(void*);

void frame_module_init(u64 byte_size) {
  fp_top = malloc(byte_size);
  fp_bottom = fp_top + byte_size;
  fp = fp_top;
}

void frame_set_int(FrameSlot slot, i64 val) {
  ((i64*)fp)[slot] = val;
}

void frame_set_float(FrameSlot slot, double val) {
  ((double*)fp)[slot] = val;
}

i64 frame_get_int(FrameSlot slot) {
  return ((i64*)fp)[slot];
}

double frame_get_float(FrameSlot slot) {
  return ((double*)fp)[slot];
}

void frame_alloc(uint slot_count) {
  fp += slot_count * SLOT_SIZE;
  assert(fp <= fp_bottom && "frame overflow");
}

void frame_dealloc(uint slot_count) {
  fp -= slot_count * SLOT_SIZE;
  assert(fp >= fp_top && "frame underflow");
}
