#pragma once

#include "project/project.h"

typedef byte FrameSlot;

STRUCT($Object);

//! @brief Storage unit for local (auto) variables
STRUCT(Frame);

//! @brief Frame constructor
Frame* new_frame(u64 size);

//! @brief Frame destructor
void delete_frame(Frame*);

/*!
 * @brief Return current frame; replace it with given frame
 *
 * Replaces frame with a new one.
 * Old frame returned and can be installed again later.
 *
 * @note Initially returns NULL, because there is no default frame
 */
Frame* frame_exchange(Frame*);

//! @brief Type generic frame_get function
$Int frame_get(FrameSlot);

/*!
 * @defgroup frame_get<T>
 * @brief Fetch frame variable
 */
//!{
#define frame_geti(SLOT) frame_get(SLOT)
#define frame_getf(SLOT) ($Float)frame_get(SLOT)
#define frame_geto(SLOT) ($Object*)frame_get(SLOT)
//!}

//! @brief Type generic frame_set function
void frame_set(FrameSlot, $Int val);

/*!
 * @defgroup frame_set<T>
 * @brief Store frame variable
 */
//!{
#define frame_seti(SLOT, VAL) frame_set(SLOT, VAL)
#define frame_setf(SLOT, VAL) frame_set(SLOT, ($Float)VAL)
#define frame_seto(SLOT, VAL) frame_set(SLOT, ($Object*)VAL)
//!}

//! @brief Push new @p slot_count slots onto frame
void frame_push(uint slot_count);

//! @brief Pop last @p slot_count slots from frame
void frame_pop(uint slot_count);
