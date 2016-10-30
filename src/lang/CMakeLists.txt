project(lang)

set(
  src
  runtime/frame.c
  runtime/eval.c
  runtime/env.c
)

add_library(lang STATIC ${src})
