#pragma once

#include "project/project.h"

/*!
 * @brief Operation codes
 *
 * -- Naming hints --
 * L: local slot (1 byte)
 * I: immediate (size depends on the opcode)
 * digits: constant (requires no explicit operand, encoded in memory)
 */
ENUM(Opcode) {
  OP_END, //!< stop evaluation

  OP_ADDI, //!< local += imm32
  OP_ADDL, //!< local += local

  OP_SUBI, //!< local -= imm32
  OP_SUBL, //!< local -= local

  OP_MOVL, //!< local = local
  OP_MOVI, //!< local = imm64

  OP_JNZ, //!< IF (local != 0) GOTO imm16

  OP_QLOADI, //!< local1 = local2[imm8]
  OP_QLOADL, //!< local1 = local2[local3]

  OP_QSTOREII, //!< local[imm8] = imm64
  OP_QSTOREIL, //!< local1[imm8] = local2
  OP_QSTORELI, //!< local1[local2] = imm64
  OP_QSTORELL, //!< local1[local2] = local3
};

