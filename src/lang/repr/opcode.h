#pragma once

#include "project/project.h"

/*!
 * @brief Operation codes
 *
 * -- Naming hints --
 * L: local slot (1 byte)
 * I: immediate (size depends on the opcode)
 */
ENUM(Opcode) {
  OP_END, //!< stop evaluation

  OP_ADD1, //!< local += 1
  OP_ADDI, //!< local += imm32
  OP_ADDL, //!< local += local

  OP_SUB1, //!< local -= 1
  OP_SUBI, //!< local -= imm32
  OP_SUBL, //!< local -= local

  OP_MOV0, //!< local = 0
  OP_MOVL, //!< local = local
  OP_MOVI, //!< local = imm64

  OP_JNZ, //!< IF (local != 0) GOTO imm16
};
