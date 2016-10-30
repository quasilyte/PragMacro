#pragma once

#include "project/project.h"

typedef byte FrameSlot;

//! @brief Storage unit for local (auto) variables
STRUCT(Frame) {
  byte* top;
  byte* bottom;
  byte* ptr;
};

//! @brief Prepare frame; allocate @p byte_size bytes
void frame_init(Frame*, u64 byte_size);

/*!
 * @brief Return current frame; replace it with given frame
 *
 * Replaces frame with a new one.
 * Old frame returned and can be installed again later.
 *
 * @warning Do not modify passed Frame until you get it back (next exchange call)
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
void frame_alloc(uint slot_count);

//! @brief Pop last @p slot_count slots from frame
void frame_dealloc(uint slot_count);
