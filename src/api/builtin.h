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

//! @brief Type of all user defined structs
typedef void* Struct;

typedef struct Token Token;
struct Token {/* Opaque */};

/*!
 * @section Array container
 */

//! @brief Mono type elems; indexed by {int} keys; Ordered & contiguous
typedef void* Array;

/*!
 * @defgroup <T>Array
 * @brief Type specialized arrays; fully compatible with untyped Array
 *
 * Advantages of using specialized arrays:
 * 1) They make API more specific and clear
 * 2) Its possible to use native indexing with them
 */
//!{
typedef int* IntArray;
typedef float* FloatArray;
typedef char* CharArray;
//!}

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
 * @defgroup Ts
 * @brief Create a new array from passed elements
 */
//!{
Array ints(int elem, ...);
Array floats(float elem, ...);
Array chars(char elem, ...);
Array tokens(Token elem, ...);
Array arrays(Array elem, ...);
Array structs(Struct elem, ...);
//!}

/*!
 * @defgroup new_Ts
 * @brief Create a new, empty array; Fills {len} elements with zero value
 */
//!{
Array new_ints(int len);
Array new_floats(int len);
Array new_chars(int len);
Array new_tokens(int len);
Array new_arrays(int len);
Array new_structs(int len);
//!}

/*!
 * @defgroup set_T
 * @brief Change single array element value; {idx} should be in array bounds
 */
//!{
void set_int(Array, int idx, int val);
void set_float(Array, int idx, float val);
void set_char(Array, int idx, char val);
void set_token(Array, int idx, Token val);
void set_array(Array, int idx, Array val);
void set_struct(Array, int idx, Array val);
//!}

/*!
 * @defgroup push_T
 * @brief Add {val} to the end of {Array}; increases len
 */
//!{
void push_int(Array, int val);
void push_float(Array, float val);
void push_char(Array, char val);
void push_token(Array, Token val);
void push_array(Array, Array val);
void push_struct(Array, Struct val);
//!}

/*!
 * @defgroup get_T
 * @brief Get value stored inside {Array} in {idx} cell
 */
//!{
int get_int(Array, int idx);
float get_float(Array, int idx);
char get_char(Array, int idx);
Token get_token(Array, int idx);
Array get_array(Array, int idx);
Struct get_struct(Array, int idx);
//!}

/*!
 * @defgroup pop_T
 * @brief Remove and return last {Array} element; decreases len
 */
//!{
int pop_int(Array);
float pop_float(Array);
char pop_char(Array);
Token pop_token(Array);
Array pop_array(Array);
Struct pop_struct(Array);
//!}

/*!
 * @defgroup find_T_index
 * @brief Seeks for {needle} index inside {Array}; -1 when not found
 */
//!{
int find_int_index(Array, int needle);
int find_float_index(Array, float needle);
int find_char_index(Array, char needle);
int find_token_index(Array, Token needle);
int find_array_index(Array, Array needle);
//!}

/*!
 * @defgroup is_Ts
 * @brief Returns 1 if array is specifically tagged, 0 otherwise
 */
//!{
int is_ints(Array);
int is_floats(Array);
int is_chars(Array);
int is_tokens(Array);
int is_arrays(Array);
int is_structs(Array);
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
void print_token(Token);
void print_array(Array);
void print_struct(Struct);
//!}

/*!
 * @section Keywords
 */

//! @brief Define new struct type
#define type(NAME) \
  typedef struct NAME NAME; \
  struct NAME

#define each(KEY, VALUE) \
  for (KEY;;) for (VALUE;)

#define each_value(VALUE) \
  for (VALUE;)

#define each_key(KEY) \
  for (KEY;)

#define in ;((void*)0) == (void*)&

