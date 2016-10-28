project(core)

set(
  src
  ast/ast.c
)

add_library(core STATIC ${src})
