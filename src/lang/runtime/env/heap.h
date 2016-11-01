#pragma once

#include "project/project.h"

STRUCT(Heap);

//! @brief Heap constructor
Heap* new_heap(u64 size);

//! @brief Heap destructor
void delete_heap(Heap*);

//! @see frame_exchange; this function has same notes and warnings
Heap* heap_exchange(Heap*);

//! @brief Return @p size bytes of zero-initialized memory
void* heap_alloc(uint size) HOT;

//! @brief Clear entire heap. Shrinks memory pools if needed
void heap_clear(void);
