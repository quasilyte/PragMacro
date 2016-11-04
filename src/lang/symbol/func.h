#pragma once

#include "project/project.h"

//! @brief Function info
STRUCT(Func) {
  u32 id;
  u32 frame_size; //!< Bytes on frame needed
  u64 addr; //!< Absolute address inside ProgramCounter
};
