#pragma once

#include "project/project.h"

//! @brief Initialize heap memory
void heap_init(u64 size);

//! @brief Return @p size bytes of zero-initialized memory
void* heap_alloc(uint size) HOT;

//! @brief Clear entire heap. Shrinks memory pools if needed
void heap_clear(void);
