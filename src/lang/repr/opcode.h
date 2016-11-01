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

  OP_QLOAD0, //!< local1 = local2[0]
  OP_QLOADI, //!< local1 = local2[imm8]
  OP_QLOADL, //!< local1 = local2[local3]

  OP_QSTORE00, //!< local[0] = 0
  OP_QSTORE0I, //!< local[0] = imm64
  OP_QSTORE0L, //!< local1[0] = local2
  OP_QSTOREI0, //!< local[imm8] = 0
  OP_QSTOREII, //!< local[imm8] = imm8
  OP_QSTOREIL, //!< local1[imm8] = local2
  OP_QSTOREL0, //!< local1[local2] = 0
  OP_QSTORELI, //!< local1[local2] = imm8
  OP_QSTORELL, //!< local1[local2] = local3
};

