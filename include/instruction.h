#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdint.h>

// Operation code
typedef enum OPCODE {
    OPCODE_LOAD   = 0x03,
    OPCODE_OPIMM  = 0x13,
    OPCODE_AUIPC  = 0x17,
    OPCODE_STORE  = 0x23,
    OPCODE_OP     = 0x33,
    OPCODE_LUI    = 0x37,
    OPCODE_BRANCH = 0x63,
    OPCODE_JALR   = 0x67,
    OPCODE_JAL    = 0x6f,
    OPCODE_SYSTEM = 0x73
} OPCODE;

// funct3 for load
typedef enum LOAD_INST {
    LOAD_LB  = 0,
    LOAD_LH  = 1,
    LOAD_LW  = 2,
    LOAD_LBU = 4,
    LOAD_LHU = 5
} LOAD_INST;

// funct3 for op-imm
typedef enum OPIMM_INST {
    OPIMM_ADDI  = 0,
    OPIMM_SLLI  = 1,
    OPIMM_SLTI  = 2,
    OPIMM_SLTIU = 3,
    OPIMM_XORI  = 4,
    OPIMM_SRI   = 5,
    OPIMM_ORI   = 6,
    OPIMM_ANDI  = 7,
} OPIMM_INST;

// funct7 for right-shift instructions
typedef enum SHIFT_TYPE {
    SHIFT_LOGICAL    = 0x00,
    SHIFT_ARITHMETIC = 0x20
} SHIFT_TYPE;

// funct3 for store
typedef enum STORE_INST {
    STORE_SB = 0,
    STORE_SH = 1,
    STORE_SW = 2
} STORE_INST;

// funct3 for op
typedef enum OP_INST {
    OP_ADDSUB = 0,
    OP_SLL    = 1,
    OP_SLT    = 2,
    OP_SLTU   = 3,
    OP_XOR    = 4,
    OP_SR     = 5,
    OP_OR     = 6,
    OP_AND    = 7
} OP_INST;

// funct7 for add o. sub
typedef enum ADDSUB_TYPE {
    ADDSUB_ADD = 0x00,
    ADDSUB_SUB = 0x20
} ADDSUB_TYPE;

// funct3 for branch
typedef enum BRANCH_INST {
    BRANCH_BEQ  = 0,
    BRANCH_BNE  = 1,
    BRANCH_BLT  = 4,
    BRANCH_BGE  = 5,
    BRANCH_BLTU = 6,
    BRANCH_BGEU = 7
} BRANCH_INST;

// funct3 for sys
typedef enum SYSTEM_INST {
    SYSTEM_CALL = 0x000
    // Possible expansion in future
} SYSTEM_INST;

// System call codes
typedef enum SCALL_CODE {
    SCALL_PRINT_INT      =  1,
    SCALL_PRINT_STR      =  4,
    SCALL_EXIT           = 10,
    SCALL_PRINT_CHAR     = 11,
    SCALL_PRINT_HEX      = 34,
    SCALL_PRINT_BIN      = 35,
    SCALL_PRINT_UINT     = 36,
    SCALL_RAND_INT       = 41,
    SCALL_RAND_INT_BOUND = 42,
    SCALL_EXIT_CODE      = 93
} SCALL_CODE;

// Size of data in bits
typedef enum BITSIZE {
    BITSIZE_BYTE     =  8,
    BITSIZE_HALFWORD = 16,
    BITSIZE_WORD     = 32
} BITSIZE;

// Size of data in bytes
typedef enum BYTE_LENGTH {
    LENGTH_BYTE     = 1,
    LENGTH_HALFWORD = 2,
    LENGTH_WORD     = 4
} BYTE_LENGTH;

// 32-bit single instruction
typedef uint32_t instruction_t;

// Converts 4-byte array into single 32-bit instruction
instruction_t convert_word_to_inst(const uint8_t *byteArr);

// Sign-extends input values to 32-bits
uint32_t sign_extend_val(uint32_t val, int bitLength);

// Retrieves opcode from instruction
OPCODE get_opcode(instruction_t inst);

// Retrieves rd from instruction, not for use with s- or b-type
uint8_t get_rd(instruction_t inst);

// Retrieves funct3 from instruction, not for use with u- or j-type
uint8_t get_funct3(instruction_t inst);

// Retrieves rs1 from instruction, not for use with u- or j-type
uint8_t get_rs1(instruction_t inst);

// Retrieves rs2 from instruction, not for use with i-, u-, or j-type
uint8_t get_rs2(instruction_t inst);

// Retrieves funct7 from instruction, only for use with r-type
uint8_t get_funct7(instruction_t inst);

// Retrives immediate val from instruction, only for use with i-type
uint32_t get_imm_itype(instruction_t inst);

// Retrives immediate val from instruction, only for use with s-type
uint32_t get_imm_stype(instruction_t inst);

// Retrives immediate val from instruction, only for use with b-type
uint32_t get_imm_btype(instruction_t inst);

// Retrives immediate val from instruction, only for use with u-type
uint32_t get_imm_utype(instruction_t inst);

// Retrives immediate val from instruction, only for use with j-type
uint32_t get_imm_jtype(instruction_t inst);

#endif
