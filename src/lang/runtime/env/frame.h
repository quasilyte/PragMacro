#pragma once

#include "project/project.h"

typedef byte FrameSlot;

STRUCT($Object);
STRUCT(Func);

STRUCT(CallInfo) {
  const Func* func;
  u64 ret_addr;
};

//! @brief Initialize frame memory
void frame_init(u64 size);

//! @brief Type generic frame_get function
$Int frame_get(FrameSlot) HOT;

/*!
 * @defgroup frame_get<T>
 * @brief Fetch local variable from frame memory
 */
//!{
#define frame_geti(SLOT) frame_get(SLOT)
#define frame_getf(SLOT) ($Float)frame_get(SLOT)
#define frame_geto(SLOT) ($Object*)frame_get(SLOT)
//!}

//! @brief Type generic frame_set function
void frame_set(FrameSlot, $Int val) HOT;

/*!
 * @defgroup frame_set<T>
 * @brief Store local variable in frame memory
 */
//!{
#define frame_seti(SLOT, VAL) frame_set(SLOT, VAL)
#define frame_setf(SLOT, VAL) frame_set(SLOT, ($Float)VAL)
#define frame_seto(SLOT, VAL) frame_set(SLOT, ($Object*)VAL)
//!}

//! @brief Create new activation record (winding 1 level)
void frame_push(const Func*, u64 ret_addr);

//! @brief Destroy last activation record (unwinding 1 level)
//const CallInfo* frame_pop(void);
u64 frame_pop(void);
