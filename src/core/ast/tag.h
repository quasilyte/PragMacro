#pragma once

#include "core/project/project.h"

//! @brief Ast types
ENUM(AstTag) {
  // Values
  AST_INT_CONST,

  // Expressions
  AST_INT_EXPR_ADD,
  AST_INT_VAR,

  // Statements
  AST_INT_CONST_ASSIGN,
  AST_INT_EXPR_ASSIGN,
  AST_INT_CONST_ADDASSIGN,
  AST_INT_EXPR_ADDASSIGN,
};
