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
 * Once installed, frame contents are destructured,
 * so even if you modify given frame from outside,
 * changes will not affect frame module state.
 * Note however, that after exchange called again,
 * returned frame pointer will reflect mutated state.
 *
 * @note Initially returns NULL, because there is no default frame
 */
Frame* frame_exchange(Frame*);

/*!
 * @defgroup frame_get<T>
 * @brief Fetch frame variable
 */
//!{
$int frame_geti(FrameSlot);
$float frame_getf(FrameSlot);
//!}

/*!
 * @defgroup frame_set<T>
 * @brief Store frame variable
 */
//!{
void frame_seti(FrameSlot, $int val);
void frame_setf(FrameSlot, $float val);
//!}

//! @brief Push new @p slot_count slots onto frame
void frame_alloc(uint slot_count);

//! @brief Pop last @p slot_count slots from frame
void frame_dealloc(uint slot_count);
