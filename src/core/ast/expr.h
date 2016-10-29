#pragma once

/*!
 * @brief Expressions -- object values of Ast
 */

#include "core/project/project.h"

STRUCT(Ast);

//! @brief Binary operation
STRUCT(ExprBinOp) {
  const Ast* lhs;
  const Ast* rhs;
};
