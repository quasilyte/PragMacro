#include "lang/runtime/env/heap.h"

#include "cstd/stdlib.h"
#include "cstd/string.h"

static byte* heap_top;
static const byte* heap_bottom;
static byte* heap_ptr;

void heap_init(u64 size) {
  assert(size >= 256 && "heap size is indecently low");

  heap_top = calloc(size, 1);
  heap_bottom = heap_top + size;
  heap_ptr = heap_top;
}

void* heap_alloc(uint size) {
  dev_assert(heap_ptr != NULL && "heap not initialized");

  // Note: no memory zeroing here.
  // To help perfomance, we zero-fill memory on deallocation

  byte* allocated = heap_ptr;
  heap_ptr += size;

  assert(heap_ptr <= heap_bottom && "heap overflow");
  return allocated;
}

void heap_clear(void) {
  dev_assert(heap_ptr != NULL && "heap not initialized");

  memset(heap_top, 0, heap_ptr - heap_top);
  heap_ptr = heap_top;
}
