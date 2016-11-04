#pragma once

#include "project/project.h"
#include "lang/symbol/func.h"

void rtti_init(const Func* func_list);

const Func* rtti_get_func(u32 fn_id);
