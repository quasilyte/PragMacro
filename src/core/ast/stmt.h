#pragma once

/*!
 * @brief Statements -- object values of Ast
 */

#include "core/project/project.h"
#include "core/runtime/frame.h"

STRUCT(Ast);

STRUCT(StmtAssign) {
  FrameSlot slot;
  const Ast* init;
};
