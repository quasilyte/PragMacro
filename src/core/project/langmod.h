#pragma once

/*!
 * @brief A set of macro to make C better suitable for this project
 */

//! @brief Switch without fallthrough
#define SWITCH switch
#define CASE break; case
#define DEFAULT break; default

//! @brief Struct with auto typedef
#define STRUCT(T) \
  typedef struct T T; \
  struct T

//! @brief Enum with auto typedef
#define ENUM(E) \
  typedef enum E E; \
  enum E
