#include "lang/runtime/env/rtti.h"

#include "cstd/stdlib.h"

static const Func* rtti_fn_list;

void rtti_init(const Func* func_list) {
  rtti_fn_list = func_list;
}

const Func* rtti_get_func(u32 fn_id) {
  return rtti_fn_list + fn_id;
}
