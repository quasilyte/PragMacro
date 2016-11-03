#include "lang/runtime/object.h"

i64 obj_load(const $Object* obj, u32 idx) {
  return ((i64*)obj->data)[idx];
}

void obj_store($Object* obj, u32 idx, i64 val) {
  ((i64*)obj->data)[idx] = val;
}

