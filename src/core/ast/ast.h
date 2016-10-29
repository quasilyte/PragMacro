#pragma once

/*!
 * @brief Ast type and related functions
 */

#include "core/project/project.h"
#include "core/ast/tag.h"
#include "core/ast/meta.h"
#include "core/runtime/frame.h"

//! @brief Polymorphic expression or statement unit
STRUCT(Ast) {
  const AstMeta* meta;
  void* object;
};

void init_ast_module(void);

void eval(const Ast*) $HOT;
i64 eval_int(const Ast*) $HOT;

Ast* ast_int_const(i64);
Ast* ast_int_expr_add(const Ast* lhs, const Ast* rhs);
Ast* ast_int_var(FrameSlot);
Ast* ast_int_const_assign(FrameSlot, i64 val);
Ast* ast_int_expr_assign(FrameSlot, const Ast* expr);
Ast* ast_int_const_addassign(FrameSlot, i64 val);
Ast* ast_int_expr_addassign(FrameSlot, const Ast* expr);
