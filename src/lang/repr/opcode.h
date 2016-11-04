#pragma once

#include "project/project.h"

/*!
 * @brief Operation codes
 *
 * -- Naming hints --
 * L: local slot (1 byte)
 * B: 8 bit (byte) immediate
 * W: 16 bit (word) immediate
 * D: 32 bit (double word) immediate
 * Q: 64 bit (quad word) immediate
 */
ENUM(Opcode) {
  OP_END, //!< stop evaluation 

  OP_ADD_LI, //!< local += imm32
  OP_ADD_LL, //!< local += local

  OP_SUB_LI, //!< local -= imm32
  OP_SUB_LL, //!< local -= local

  OP_MOV_LI, //!< local = imm64
  OP_MOV_LL, //!< local = local

  OP_JNZ, //!< IF (local != 0) GOTO imm16

  OP_LOAD_LLI, //!< local1 = local2[imm8]
  OP_LOAD_LLL, //!< local1 = local2[local3]

  OP_STORE_LII, //!< local[imm8] = imm64
  OP_STORE_LIL, //!< local1[imm8] = local2
  OP_STORE_LLI, //!< local1[local2] = imm64
  OP_STORE_LLL, //!< local1[local2] = local3

  OP_RET, //!< return from function
  OP_CALL, //!< call functions
  OP_CALL_VOID, //!< call function / ignore return value
};

