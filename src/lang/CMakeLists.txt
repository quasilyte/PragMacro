project(lang)

set(
  src
  runtime/env/pc.c
  runtime/env/frame.c
  runtime/env/heap.c
  runtime/eval.c
  runtime/object.c
  runtime/array.c
)

add_library(lang STATIC ${src})
