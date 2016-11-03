/*!
 * @brief Language API
 * @note This file is never parsed with interpreter
 *
 * For more exhaustive documentation look inside specs.
 * If you wish to find a compact list of definitions,
 * you should look elsewhere (though you can take a look
 * at minified version of this file with all comments removed).
 *
 * #TODO: put links here
 */

/*!
 * @section Keywords
 */

#ifndef NULL
  #define NULL ((void*)0)
#endif

#define each(KEY, VALUE) \
  for (KEY;;) for (VALUE;)

#define each_value(VALUE) \
  for (VALUE;)

#define each_key(KEY) \
  for (KEY;)

#define in ;((void*)0) == (void*)&

/*!
 * @section Token related
 */

typedef struct Token Token;
struct Token {/* Opaque */};

/*!
 * @section Struct related
 */

//! @brief Untyped struct. "Parent" type of any struct
typedef void* Struct;

/*!
 * @brief Type specialized struct; fully compatible with untyped Struct
 */
#define Struct(T) struct T*

#define make(T, ...) NULL

/*!
 * @section Array related
 */

//! @brief Untyped Array. "Parent" type of any array
typedef void* Array;

/*!
 * @brief Type specialized arrays; fully compatible with untyped Array
 */
#define Array(T) T*

//! @brief Array length
int len(Array);

//! @brief Pushes each {src} element into {dst}
void append(Array dst, Array src);

/*!
 * @brief Deep copy of {count} elements from {Array} starting from {idx}
 *
 * Copies sub array from the original.
 * Copied elements has no memory overlap with original, so
 * modifications are not shared between them.
 *
 * @param[in] idx Positive or negative (reverse) starting index
 * @param[in] count Positive count or -1 to copy all rest elements
 */
Array copy(Array, int idx, int count);

/*!
 * @brief Shallow copy {count} elements from {Array} starting from {idx}
 *
 * Takes mutable array slice.
 * Sliced and original arrays share same memory, so
 * modifications of one causes mutations of another.
 *
 * @see copy function to read about @p idx & @p count params
 */
Array slice(Array, int idx, int count);

/*!
 * @defgroup sort_*
 * @brief In-place array sort
 */
//!{
void sort_desc(Array);
void sort_asc(Array);
//!}

//! @brief In-place array reverse
void reverse(Array);

/*!
 * @defgroup is_Ts
 * @brief Returns 1 if array is specifically tagged, 0 otherwise
 */
//!{
int is_ints(Array);
int is_floats(Array);
int is_chars(Array);
int is_arrays(Array);
int is_structs(Array);
//!}

/*!
 * @defgroup Ts
 * @brief Create a new array from passed elements
 */
//!{
Array(int) ints(int elem, ...);
Array(float) floats(float elem, ...);
Array(char) chars(char elem, ...);
Array(Array) arrays(Array elem, ...);
Array(Struct) structs(Struct elem, ...);
//!}

/*!
 * @defgroup new_Ts
 * @brief Create a new, empty array; Fills {len} elements with zero value
 */
//!{
Array(int) new_ints(int len);
Array(float) new_floats(int len);
Array(char) new_chars(int len);
Array(Array) new_arrays(int len);
Array(Struct) new_structs(int len);
//!}

/*!
 * @defgroup set_T
 * @brief Change single array element value; {idx} should be in array bounds
 */
//!{
void set_int(Array(int), int idx, int val);
void set_float(Array(float), int idx, float val);
void set_char(Array(char), int idx, char val);
void set_array(Array(Array), int idx, Array val);
void set_struct(Array(Struct), int idx, Array val);
//!}

/*!
 * @defgroup push_T
 * @brief Add {val} to the end of {Array}; increases len
 */
//!{
void push_int(Array(int), int val);
void push_float(Array(float), float val);
void push_char(Array(char), char val);
void push_array(Array(Array), Array val);
void push_struct(Array(Struct), Struct val);
//!}

/*!
 * @defgroup get_T
 * @brief Get value stored inside {Array} in {idx} cell
 */
//!{
int get_int(Array(int), int idx);
float get_float(Array(float), int idx);
char get_char(Array(char), int idx);
Array get_array(Array(Array), int idx);
Struct get_struct(Array(Struct), int idx);
//!}

/*!
 * @defgroup pop_T
 * @brief Remove and return last {Array} element; decreases len
 */
//!{
int pop_int(Array(int));
float pop_float(Array(float));
char pop_char(Array(char));
Array pop_array(Array(Array));
Struct pop_struct(Array(Struct));
//!}

/*!
 * @section I/O functions
 */

/*!
 * @defgroup print_T
 * @brief Print given value to the stdout
 */
//!{
void print_int(int);
void print_float(float);
void print_char(char);
void print_array(Array);
void print_struct(Struct);
//!}
