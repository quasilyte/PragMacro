#include "core/ast/ast.h"

#include "core/ast/expr.h"
#include "core/ast/stmt.h"

#include "cstd/stdlib.h"

typedef void(*eval_fn)(const void*);
typedef i64(*eval_int_fn)(const void*);

void init_ast_module(void) {
  /* Could initialize memory arena for AST nodes */
}

/*!
 * @section Private functions
 */

$CONST FrameSlot to_frame_slot(const void* slot) {
  return (FrameSlot)(u64)slot;
}

static Ast* ast_new(const AstMeta* meta, void* object) {
   Ast* ast = malloc(sizeof(Ast));
   ast->meta = meta;
   ast->object = object;
   return ast;
}

static StmtAssign* stmt_assign_new(FrameSlot slot, const void* init) {
  StmtAssign* stmt = malloc(sizeof(StmtAssign));
  stmt->slot = slot;
  stmt->init = init;
  return stmt;
}

/*!
 * @section Eval functions
 */

void eval(const Ast* x) {
  x->meta->eval(x->object);
}

i64 eval_int(const Ast* x) {
  return x->meta->eval_int(x->object);
}

$CONST i64 int_const_eval_int(const void* x) {
  return (i64)x;
}

i64 int_add_eval_int(const ExprBinOp* expr) {
  return eval_int(expr->lhs) + eval_int(expr->rhs);
}

i64 int_var_eval_int(const void* x) {
  return frame_get_int(to_frame_slot(x));
}

void int_const_assign_eval(const StmtAssign* stmt) {
  frame_set_int(stmt->slot, (i64)stmt->init);
}

void int_expr_assign_eval(const StmtAssign* stmt) {
  frame_set_int(stmt->slot, eval_int(stmt->init));
}

void int_const_addassign_eval(const StmtAssign* stmt) {
  i64 old_val = frame_get_int(stmt->slot);
  frame_set_int(stmt->slot, old_val + (i64)stmt->init);
}

void int_expr_addassign_eval(const StmtAssign* stmt) {
  i64 old_val = frame_get_int(stmt->slot);
  frame_set_int(stmt->slot, old_val + eval_int(stmt->init));
}

/*!
 * @section AstMeta init
 */

#define GEN_EXPR_META(NAME, TAG) \
  static const AstMeta NAME##_meta = { \
    NULL, \
    (eval_int_fn)NAME##_eval_int, \
    TAG \
  }

#define GEN_STMT_META(NAME, TAG) \
  static const AstMeta NAME##_meta = { \
    (eval_fn)NAME##_eval, \
    NULL, \
    TAG \
  }

GEN_EXPR_META(int_const, AST_INT_CONST);
GEN_EXPR_META(int_add, AST_INT_EXPR_ADD);
GEN_EXPR_META(int_var, AST_INT_VAR);

GEN_STMT_META(int_const_assign, AST_INT_CONST_ASSIGN);
GEN_STMT_META(int_expr_assign, AST_INT_EXPR_ASSIGN);
GEN_STMT_META(int_const_addassign, AST_INT_CONST_ADDASSIGN);
GEN_STMT_META(int_expr_addassign, AST_INT_EXPR_ADDASSIGN);

#undef GEN_EXPR_META
#undef GEN_STMT_META

/*!
 * @section Ast constructors
 */

Ast* ast_int_const(i64 val) {
  return ast_new(&int_const_meta, (void*)val);
}

Ast* ast_int_expr_add(const Ast* lhs, const Ast* rhs) {
  ExprBinOp* expr = malloc(sizeof(ExprBinOp));
  expr->lhs = lhs;
  expr->rhs = rhs;
  return ast_new(&int_add_meta, expr);
}

Ast* ast_int_var(FrameSlot slot) {
  return ast_new(&int_var_meta, (void*)(i64)slot);
}

Ast* ast_int_const_assign(FrameSlot slot, i64 val) {
  return ast_new(&int_const_assign_meta, stmt_assign_new(slot, (void*)val));
}

Ast* ast_int_expr_assign(FrameSlot slot, const Ast* expr) {
  return ast_new(&int_expr_assign_meta, stmt_assign_new(slot, expr));
}

Ast* ast_int_const_addassign(FrameSlot slot, i64 val) {
  return ast_new(&int_const_addassign_meta, stmt_assign_new(slot, (void*)val));
}

Ast* ast_int_expr_addassign(FrameSlot slot, const Ast* expr) {
  return ast_new(&int_expr_addassign_meta, stmt_assign_new(slot, expr));
}
