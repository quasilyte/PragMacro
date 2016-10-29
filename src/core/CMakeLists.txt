project(core)

set(
  src
  ast/ast.c
  runtime/frame.c
)

add_library(core STATIC ${src})
