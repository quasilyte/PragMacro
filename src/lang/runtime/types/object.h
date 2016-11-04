#pragma once

#include "project/project.h"
#include "lang/runtime/types/tag.h"

STRUCT($Object) {
  byte* data;
  $Tag tag;
};

$Int obj_load(const $Object*, u32 idx) HOT;

void obj_store($Object*, u32 idx, $Int val) HOT;
