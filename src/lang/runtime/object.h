#pragma once

#include "project/project.h"
#include "lang/runtime/tag.h"

STRUCT($Object) {
  byte* data;
  $Tag tag;
};

i64 obj_qload(const $Object*, u32 idx) HOT;

void obj_store($Object*, u32 idx, i64 val) HOT;
