#include "lang/runtime/types/array.h"

#include "cstd/stdlib.h"

#include "lang/runtime/env/heap.h"

$Array* new_array($Tag tag, u32 len) {
  $Array* arr = malloc(sizeof($Array));

  arr->tag = tag;
  arr->len = len;
  arr->cap = len;
  arr->data = heap_alloc(len * sizeof(void*));

  return arr;
}
