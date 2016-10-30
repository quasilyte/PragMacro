project(lang)

set(
  src
  runtime/frame.c
  runtime/eval.c
  runtime/pc.c
)

add_library(lang STATIC ${src})
