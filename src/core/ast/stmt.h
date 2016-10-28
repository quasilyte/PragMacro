#pragma once

#include "core/project/project.h"

STRUCT(Ast);

STRUCT(StmtAssign) {
  int id;
  const Ast* init;
}
