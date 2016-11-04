#pragma once

#include "project/project.h"

typedef byte FrameSlot;

STRUCT($Object);

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

//! @brief Preserve current frame @p count slots; go to next frame
void frame_push(uint count);

//! @brief Restore previous frame @p count slots; go to prev frame
void frame_pop(uint count);
