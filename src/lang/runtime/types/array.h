#pragma once

#include "project/project.h"
#include "lang/runtime/tag.h"

STRUCT($Array) {
  void* data;

  $Tag tag;
  u32 len;
  u32 cap;
};

$Array* new_array($Tag tag, u32 len);
