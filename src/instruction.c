#include "../include/instruction.h"

#include <stddef.h>

static inline bool is_valid_opcode(const OPCODE_E code) {
    constexpr OPCODE_E g_opcodeReference[] = {
        OPCODE_LOAD, OPCODE_OPIMM, OPCODE_AUIPC, OPCODE_STORE, OPCODE_OP,
        OPCODE_LUI, OPCODE_BRANCH, OPCODE_JALR, OPCODE_JAL, OPCODE_SYSTEM
    };
    constexpr uint8_t g_numOpcodes = 10;

    for (size_t i = 0; i < g_numOpcodes; i++) {
        if (code == g_opcodeReference[i]) {
            return true;
        }
    }

    return false;
}

static inline uint32_t sign_extend_val(const uint32_t val, const int bitLength) {
    uint32_t newVal = val;
    uint32_t signMask = val >> (bitLength - 1);

    if (signMask == 1) {
        int ex = LENGTH_WORD_IN_BITS - bitLength - 1;

        for (size_t i = 0; i < LENGTH_WORD_IN_BITS - 1; i++) {
            signMask <<= 1;

            if (ex != 0) {
                ex--;
                signMask += 1;
            }
        }
        newVal |= signMask;
    }
    return newVal;
}

EncodedInstruction_t convert_word_to_inst(const uint8_t byteArr[LENGTH_WORD]) {
    EncodedInstruction_t inst = 0;

    for (size_t i = LENGTH_WORD - 1; i < LENGTH_WORD; i--) {
        inst <<= LENGTH_BYTE_IN_BITS;
        inst |= byteArr[i];
    }
    return inst;
}

OPCODE_E get_opcode(const EncodedInstruction_t inst) {
    OPCODE_E code = inst & 0x7f;

    if (!is_valid_opcode(code)) {
        fatal_error(ERR_ILLEGAL_VALUE);
    }

    return code;
}

uint8_t get_rd(const EncodedInstruction_t inst) {
    return (inst & 0xf80) >> 7;
}

uint8_t get_funct3(const EncodedInstruction_t inst) {
    return (inst & 0x7000) >> 12;
}

uint8_t get_rs1(const EncodedInstruction_t inst) {
    return (inst & 0xf8000) >> 15;
}

uint8_t get_rs2(const EncodedInstruction_t inst) {
    return (inst & 0x1f00000) >> 20;
}

uint8_t get_funct7(const EncodedInstruction_t inst) {
    return (inst & 0xfe000000) >> 25;
}

uint32_t get_imm_itype(const EncodedInstruction_t inst) {
    return sign_extend_val((inst & 0xfff00000) >> 20, 12);
}

uint32_t get_imm_stype(const EncodedInstruction_t inst) {
    return sign_extend_val(((inst & 0xfe000000) >> 20)
                           | ((inst & 0xf80) >> 7), 12);
}

uint32_t get_imm_btype(const EncodedInstruction_t inst) {
    return sign_extend_val(((inst & 0x80000000) >> 19)
                           | ((inst & 0x7e000000) >> 20)
                           | ((inst & 0xf00) >> 7)
                           | ((inst & 0x80) << 4), 13);
}

uint32_t get_imm_utype(const EncodedInstruction_t inst) {
    return (inst & 0xfffff000);
}

uint32_t get_imm_jtype(const EncodedInstruction_t inst) {
    return sign_extend_val(((inst & 0x80000000) >> 11)
                           | ((inst & 0x7fe00000) >> 20)
                           | ((inst & 0x100000) >> 9)
                           | (inst & 0xff000), 21);
}
