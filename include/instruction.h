/** @file instruction.h
 *  @brief Function prototypes and enumerations for instruction operation
 *
 *  This contains the prototypes for functions that can read and return
 *  specified areas from an input instruction as well as converting a byte
 *  array into an instrution. Also contains enumerations and macros that could
 *  be beneficial when those functions are used.
 *
 *  @author DilanIsHere (Dilan Hamid)
 *  @ref https://github.com/DilanIsHere
 */

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "../include/utils.h"

#include <stdint.h>

/** 32-bit type containing a single risc-v instruction */
typedef uint32_t EncodedInstruction_t;

/** @brief Enum of instruction opcodes
 *
 *  @details
 *  Operation codes are unsigned 7-bit values specifiying the type of operation
 *  an @ref EncodedInstruction_t is encoded as. Use the @ref get_opcode function to
 *  retrieve this value from instructions.
 */
enum OPCODE_E: uint8_t {
    OPCODE_LOAD   = 0x03,   /**< Load Instruction Opcode */
    OPCODE_OPIMM  = 0x13,   /**< Op-Imm Instruction Opcode */
    OPCODE_AUIPC  = 0x17,   /**< AUIPC Instruction Opcode */
    OPCODE_STORE  = 0x23,   /**< Store Instruction Opcode */
    OPCODE_OP     = 0x33,   /**< Op Instruction Opcode */
    OPCODE_LUI    = 0x37,   /**< LUI Instruction Opcode */
    OPCODE_BRANCH = 0x63,   /**< Branch Instruction Opcode */
    OPCODE_JALR   = 0x67,   /**< JALR Instruction Opcode */
    OPCODE_JAL    = 0x6f,   /**< JAL Instruction Opcode */
    OPCODE_SYSTEM = 0x73    /**< System Instruction Opcode */
};
/** Type of instruction operation */
typedef enum OPCODE_E OPCODE_E;

/** @brief Enum of load instruction codes
 *
 *  @details
 *  Load instruction codes are unsigned 3-bit values that denote which specific
 *  type of load operation is to be performed. Use the @ref get_funct3 function
 *  to retrieve this value from the @ref EncodedInstruction_t type.
 *
 *  @important This value is only defined in instructions with the @ref OPCODE_E
 *  value @ref OPCODE_LOAD.
 */
enum LOAD_INST_E: uint8_t {
    LOAD_LB  = 0,   /**< Load Byte Code */
    LOAD_LH  = 1,   /**< Load Halfword Code */
    LOAD_LW  = 2,   /**< Load Word Code */
    LOAD_LBU = 4,   /**< Load Unsigned Byte Code */
    LOAD_LHU = 5    /**< Load Unsigned Halfword Code */
};
/** Type for variables holding load instruction codes */
typedef enum LOAD_INST_E LOAD_INST_E;

/** @brief Enum of op-immediate instruction codes
 *
 *  @details
 *  Op-imm instruction codes are unsigned 3-bit values that denote which
 *  specific type of op-imm operation is to be performed. Use the
 *  @ref get_funct function to retrieve this value from the @ref EncodedInstruction_t
 *  type.
 *
 *  @important This value is only defined in instructions with the @ref OPCODE_E
 *  value @ref OPCODE_OPIMM.
 */
enum OPIMM_INST_E: uint8_t {
    OPIMM_ADDI  = 0,    /**< Add Immediate Code */
    OPIMM_SLLI  = 1,    /**< Bitwise Logical Left-Shift Immediate Code */
    OPIMM_SLTI  = 2,    /**< Set Less Than Immediate Code */
    OPIMM_SLTIU = 3,    /**< Unsigned Set Less Than Immediate Code */
    OPIMM_XORI  = 4,    /**< Bitwise Exclusive-Or Immediate Code */
    OPIMM_SRI   = 5,    /**< Bitwise Right-Shift Immediate Code */
    OPIMM_ORI   = 6,    /**< Bitwise Or Immediate Code */
    OPIMM_ANDI  = 7,    /**< Bitwise And Immediate Code */
};
/** Type for variables holding op-imm instruction codes */
typedef enum OPIMM_INST_E OPIMM_INST_E;

/** 7-bit unsigned enum for right-shift instruction type */
enum SHIFT_TYPE_E: uint8_t {
    SHIFT_LOGICAL    = 0x00,    /**< Logical Shift Type */
    SHIFT_ARITHMETIC = 0x20     /**< Arithmetic Shift Type */
};
/** Type for variables holding right-shift instruction specifiers */
typedef enum SHIFT_TYPE_E SHIFT_TYPE_E;

/** @brief Enum of store instruction codes
 *
 *  @details
 *  Store instruction codes are unsigned 3-bit values that denote which specific
 *  type of store operation is to be performed. Use the @ref get_funct3 function
 *  to retrieve this value from the @ref EncodedInstruction_t type.
 *
 *  @important This value is only defined in instructions with the @ref OPCODE_E
 *  value @ref OPCODE_STORE.
 */
enum STORE_INST_E: uint8_t {
    STORE_SB = 0,   /**< Store Byte Code */
    STORE_SH = 1,   /**< Store Halfword Code */
    STORE_SW = 2    /**< Store Word Code */
};
// 3-bit specifier for store instructions
typedef enum STORE_INST_E STORE_INST_E;

/** @brief Enum of op instruction codes
 *
 *  @details
 *  Op instruction codes are unsigned 3-bit values that denote which specific
 *  type of op operation is to be performed. Use the @ref get_funct3 function
 *  to retrieve this value from the @ref EncodedInstruction_t type.
 *
 *  @important This value is only defined in instructions with the @ref OPCODE_E
 *  value @ref OPCODE_OP.
 */
enum OP_INST_E: uint8_t {
    OP_ADDSUB = 0,  /**< Add/Sub Code */
    OP_SLL    = 1,  /**< Bitwise Logical Left-Shift Code */
    OP_SLT    = 2,  /**< Set Less Than Code */
    OP_SLTU   = 3,  /**< Unsigned Set Less Than Code */
    OP_XOR    = 4,  /**< Bitwise Exclusive-Or Code */
    OP_SR     = 5,  /**< Bitwise Right-Shift Code */
    OP_OR     = 6,  /**< Bitwise Or Code */
    OP_AND    = 7
};
// 3-bit specifier for op instructions
typedef enum OP_INST_E OP_INST_E;

/** 7-bit unsigned enum for add-sub instruction type */
enum ADDSUB_TYPE_E: uint8_t {
    ADDSUB_ADD = 0x00,
    ADDSUB_SUB = 0x20
};
// 7-bit specifier for add vs. sub instructions
typedef enum ADDSUB_TYPE_E ADDSUB_TYPE_E;

/** @brief Enum of branch instruction codes
 *
 *  @details
 *  Branch instruction codes are unsigned 3-bit values that denote which
 *  specific type of branch operation is to be performed. Use the
 *  @ref get_funct3 function to retrieve this value from the @ref EncodedInstruction_t
 *  type.
 *
 *  @important This value is only defined in instructions with the @ref OPCODE_E
 *  value @ref OPCODE_BRANCH.
 */
enum BRANCH_INST_E: uint8_t {
    BRANCH_BEQ  = 0,
    BRANCH_BNE  = 1,
    BRANCH_BLT  = 4,
    BRANCH_BGE  = 5,
    BRANCH_BLTU = 6,
    BRANCH_BGEU = 7
};
// 3-bit specifier for branch instructions
typedef enum BRANCH_INST_E BRANCH_INST_E;

/** 12-bit unsigned enum for system instruction type */
enum SYSTEM_INST_E: uint16_t {
    SYSTEM_CALL = 0x000
    // Possible expansion in future
};
// 12-bit specifier for for system instructions
typedef enum SYSTEM_INST_E SYSTEM_INST_E;

/** Unsigned enum for all possible system call codes */
enum SCALL_CODE_E: uint16_t {
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
};
// Code specifying system call type
typedef enum SCALL_CODE_E SYS_CODE_E;

enum DATA_LENGTH_E {
    LENGTH_BYTE            = 1,
    LENGTH_HALFWORD        = LENGTH_BYTE * 2,
    LENGTH_WORD            = LENGTH_HALFWORD * 2,
    LENGTH_BYTE_IN_BITS    = LENGTH_BYTE * 8,
    LENGTH_HALWORD_IN_BITS = LENGTH_BYTE_IN_BITS * LENGTH_HALFWORD,
    LENGTH_WORD_IN_BITS    = LENGTH_BYTE_IN_BITS * LENGTH_WORD
};
// Length of data in bytes or bits
typedef enum DATA_LENGTH_E DATA_LENGTH_E;

struct DecodedRType_t {
    union funct7 {
        SHIFT_TYPE_E shift   :7;
        ADDSUB_TYPE_E addsub :7;
        uint8_t zero         :7;
    };
    uint8_t rs2      :5;
    uint8_t rs1      :5;
    uint8_t rd       :5;
    OP_INST_E funct3 :3;
};

struct DecodedIType_t {
    uint32_t imm;
    uint8_t rs1 :5;
    uint8_t rd  :5;
    union funct3 {
        LOAD_INST_E load   :3;
        OPIMM_INST_E opimm :3;
        uint8_t zero       :3;
    };
};

struct DecodedSType_t {
    uint32_t imm;
    uint8_t rs2         :5;
    uint8_t rs1         :5;
    STORE_INST_E funct3 :3;
};

struct DecodedBType_t {
    uint32_t imm;
    uint8_t rs2          :5;
    uint8_t rs1          :5;
    BRANCH_INST_E funct3 :3;
};

struct DecodedUType_t {
    uint32_t imm;
    uint8_t rd :5;
};

struct DecodedJType_t {
    uint32_t imm;
    uint8_t rd :5;
};

struct DecodedInstruction_t {
    union {
      struct DecodedRType_t r;
      struct DecodedIType_t i;
      struct DecodedSType_t s;
      struct DecodedBType_t b;
      struct DecodedUType_t u;
      struct DecodedJType_t j;
    };
    OPCODE_E opcode :7;
};
typedef struct DecodedInstruction_t DecodedInstruction_t;

// Converts 4-byte array into single 32-bit instruction
EncodedInstruction_t convert_word_to_inst(const uint8_t byteArr[LENGTH_WORD]);

// Retrieves opcode from instruction
OPCODE_E get_opcode(const EncodedInstruction_t inst);

// Retrieves rd from instruction, not for use with s- or b-type
uint8_t get_rd(const EncodedInstruction_t inst);

// Retrieves funct3 from instruction, not for use with u- or j-type
uint8_t get_funct3(const EncodedInstruction_t inst);

// Retrieves rs1 from instruction, not for use with u- or j-type
uint8_t get_rs1(const EncodedInstruction_t inst);

// Retrieves rs2 from instruction, not for use with i-, u-, or j-type
uint8_t get_rs2(const EncodedInstruction_t inst);

// Retrieves funct7 from instruction, only for use with r-type
uint8_t get_funct7(const EncodedInstruction_t inst);

// Retrives immediate val from instruction, only for use with i-type
uint32_t get_imm_itype(const EncodedInstruction_t inst);

// Retrives immediate val from instruction, only for use with s-type
uint32_t get_imm_stype(const EncodedInstruction_t inst);

// Retrives immediate val from instruction, only for use with b-type
uint32_t get_imm_btype(const EncodedInstruction_t inst);

// Retrives immediate val from instruction, only for use with u-type
uint32_t get_imm_utype(const EncodedInstruction_t inst);

// Retrives immediate val from instruction, only for use with j-type
uint32_t get_imm_jtype(const EncodedInstruction_t inst);

#endif /* INSTRUCTION_H */
