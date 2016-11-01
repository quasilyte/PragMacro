#include "lang/runtime/env/heap.h"

#include "cstd/stdlib.h"
#include "cstd/string.h"

STRUCT(Heap) {
  byte* top;
  byte* bottom;
  byte* ptr;
};

static byte* heap_top;
static const byte* heap_bottom;
static byte* heap_ptr;

static Heap* current_heap = NULL;

Heap* new_heap(u64 size) {
  assert(size >= 256 && "heap size is indecently low");

  Heap* h = malloc(sizeof(Heap));

  h->top = calloc(size, 1);
  h->bottom = h->top + size;
  h->ptr = h->top;

  return h;
}

void delete_heap(Heap* heap) {
  free(heap->top);
  free(heap);

  heap_ptr = NULL;
}

Heap* heap_exchange(Heap* heap) {
  Heap* old_heap = current_heap;
  if (old_heap) {
    old_heap->ptr = heap_ptr;
  }

  heap_top = heap->top;
  heap_bottom = heap->bottom;
  heap_ptr = heap->ptr;

  current_heap = heap;

  return old_heap;
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
