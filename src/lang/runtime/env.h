#pragma once

#include "project/project.h"

STRUCT(Env) {
  const byte* pc;
};

byte pc_byte(Env*);
i32 pc_i32(Env*);
i16 pc_i16(Env*);
i64 pc_i64(Env*);
