project(pragmapp)

cmake_minimum_required(VERSION 3.0)

include_directories(
  "src" "vendor"
)

set(c_main_flags "-std=c11 -O2")
set(c_warning_flags "-Wall -Wextra")
set(
  CMAKE_C_FLAGS
  "${CMAKE_C_FLAGS} ${c_main_flags} ${c_warning_flags}"
)

# Forcing Qt Creator to display headers
file(
  GLOB_RECURSE
  header_files
  "src/*.h"
)
add_custom_target(headers SOURCES ${header_files})

add_subdirectory("src/core")

add_executable(${PROJECT_NAME} local/main.c)
target_link_libraries(
  ${PROJECT_NAME}
  core
)
