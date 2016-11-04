#pragma once

#include "project/project.h"

STRUCT(Func);

//! @brief Evaluate using current environment (PC, frame, ...)
void eval(void);

//! @brief Evaluate function
void eval_func(const Func*);
