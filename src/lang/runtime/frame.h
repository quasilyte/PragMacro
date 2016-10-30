#pragma once

#include "project/project.h"

typedef byte FrameSlot;

//! @brief Prepare frames; allocate @p byte_size bytes
void frame_module_init(u64 byte_size);

/*!
 * @defgroup frame_get_<T>
 * @brief Fetch frame variable
 */
//!{
$int frame_geti(FrameSlot);
$float frame_getf(FrameSlot);
//!}

/*!
 * @defgroup frame_set_<T>
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
