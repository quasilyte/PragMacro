#include "core/ast/ast.h"

#include "core/ast/expr.h"

#include "cstd/stdlib.h"

void init_ast_module(void) {}

i64 eval_int(const Ast* ast) {
  switch (ast->tag) {
  case AST_INT:
    return (i64)ast->object;
  case AST_ADD: {
    ExprAdd* add = ast->object;
    return eval_int(add->lhs) + eval_int(add->rhs);
  }

  default:
    assert(0 && "given Ast does not evaluate to int");
  }
}

Ast* ast_new() {
  return malloc(sizeof(Ast));
}

Ast* ast_int(i64 x) {
  Ast* ast = ast_new();
  ast->tag = AST_INT;
  ast->object = (i64*)x;
  return ast;
}

Ast* ast_add(const Ast* lhs, const Ast* rhs) {
  Ast* ast = ast_new();
  ast->tag = AST_ADD;
  ExprAdd* add = malloc(sizeof(ExprAdd));
  add->lhs = lhs;
  add->rhs = rhs;
  ast->object = add;
  return ast;
}
