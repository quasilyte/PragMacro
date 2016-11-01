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

/*!
 * @brief Assertions those value is almost 100% in code documentation
 * @note Turn off them before profiling! They really can make things slow
 */
#ifdef DEV_MODE
  #define dev_assert(X) assert(X)
#else
  #define dev_assert(X) (void)0
#endif
