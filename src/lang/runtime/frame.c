#include "lang/runtime/frame.h"

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
