#pragma once

#include "core/project/project.h"
#include "core/ast/tag.h"

STRUCT(Ast);

//! @brief Vtable-like data structure for Ast struct instances
STRUCT(AstMeta) {
  //! @brief Evaluate AST as void expression (statement)
  void(*eval)(const void*);

  //! @brief Evaluate AST as int expression
  i64(*eval_int)(const void*);

  //! @brief Descriptor to determine concrete AST type
  AstTag tag;
};
