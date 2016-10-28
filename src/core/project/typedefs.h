#pragma once

/*!
 * @brief Project-wide typedefs
 */

#include "cstd/stdint.h"
#include "cstd/assert.h"

typedef unsigned int uint;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef uint8_t i8;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef int8_t u8;

static_assert(
  sizeof(i64) == 8 &&
  sizeof(i32) == 4 &&
  sizeof(i16) == 2 &&
  sizeof(i8) == 1 &&
  sizeof(u64) == 8 &&
  sizeof(u32) == 4 &&
  sizeof(u16) == 2 &&
  sizeof(u8) == 1,
  "integer type sizes"
);

typedef double f64;
typedef float f32;

static_assert(
  sizeof(f64) == 8 &&
  sizeof(f32) == 4,
  "floating point type sizes"
);

static_assert(
  sizeof(void*) == 8,
  "pointer type sizes"
);
