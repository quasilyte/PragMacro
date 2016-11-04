#pragma once

#include "project/project.h"

//! @brief Function info
STRUCT(Func) {
  u64 addr; //!< Absolute address inside ProgramCounter
  uint frame_size; //!< Bytes on frame needed
};
