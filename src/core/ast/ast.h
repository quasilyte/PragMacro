#pragma once

#include "core/project/project.h"

//! @brief Ast types
ENUM(AstTag) {
  // Values
  AST_INT,
  AST_FLOAT,

  AST_ADD,
};

//! @brief Polymorphic expression or statement unit
STRUCT(Ast) {
  AstTag tag;
  void* object;
};

void init_ast_module(void);

//i64 eval_int(const Ast*) __attribute__((pure));
i64 eval_int(const Ast*);

Ast* ast_int(i64);
Ast* ast_add(const Ast* lhs, const Ast* rhs);
