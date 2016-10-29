#pragma once

#include "core/project/project.h"

typedef i32 FrameSlot;

//! @brief Prepare frames; allocate @p byte_size bytes
void frame_module_init(u64 byte_size);

/*!
 * @defgroup frame_get_<T>
 * @brief Fetch frame variable
 */
//!{
i64 frame_get_int(FrameSlot);
double frame_get_float(FrameSlot);
//!}

/*!
 * @defgroup frame_set_<T>
 * @brief Store frame variable
 */
//!{
void frame_set_int(FrameSlot, i64 val);
void frame_set_float(FrameSlot, double val);
//!}

//! @brief Push new @p slot_count slots onto frame
void frame_alloc(uint slot_count);

//! @brief Pop last @p slot_count slots from frame
void frame_dealloc(uint slot_count);
