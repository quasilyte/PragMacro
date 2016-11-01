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

/*!
 * @defgroup frame_get<T>
 * @brief Fetch frame variable
 */
//!{
$Int frame_geti(FrameSlot);
$Float frame_getf(FrameSlot);
$Object* frame_geto(FrameSlot);
//!}

/*!
 * @defgroup frame_set<T>
 * @brief Store frame variable
 */
//!{
void frame_seti(FrameSlot, $Int val);
void frame_setf(FrameSlot, $Float val);
//!}

//! @brief Push new @p slot_count slots onto frame
void frame_push(uint slot_count);

//! @brief Pop last @p slot_count slots from frame
void frame_pop(uint slot_count);
