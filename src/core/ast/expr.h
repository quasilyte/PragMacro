#pragma once

#include "core/project/project.h"

STRUCT(Ast);

//! @brief Binary add expression
STRUCT(ExprAdd) {
  const Ast* lhs;
  const Ast* rhs;
};
