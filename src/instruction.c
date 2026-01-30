#include "../include/instruction.h"

instruction_t convert_word_to_inst(const uint8_t *byteArr) {
    instruction_t inst = 0;

    for (int i = LENGTH_WORD - 1; i >= 0; i--) {
        inst <<= BITSIZE_BYTE;
        inst |= byteArr[i];
    }
    return inst;
}

uint32_t sign_extend_val(uint32_t val, int bitLength) {
    uint32_t newVal = val;
    val >>= bitLength - 1;

    if (val == 1) {
        int ex = BITSIZE_WORD - bitLength - 1;

        for (int i = 0; i < BITSIZE_WORD - 1; i++) {
            val <<= 1;

            if (ex != 0) {
                ex--;
                val += 1;
            }
        }
        newVal |= val;
    }
    return newVal;
}

OPCODE get_opcode(instruction_t inst) {
    return (OPCODE)(inst & 0x7f);
}

uint8_t get_rd(instruction_t inst) {
    return (inst & 0xf80) >> 7;
}

uint8_t get_funct3(instruction_t inst) {
    return (inst & 0x7000) >> 12;
}

uint8_t get_rs1(instruction_t inst) {
    return (inst & 0xf8000) >> 15;
}

uint8_t get_rs2(instruction_t inst) {
    return (inst & 0x1f00000) >> 20;
}

uint8_t get_funct7(instruction_t inst) {
    return (inst & 0xfe000000) >> 25;
}

uint32_t get_imm_itype(instruction_t inst) {
    return sign_extend_val((inst & 0xfff00000) >> 20, 12);
}

uint32_t get_imm_stype(instruction_t inst) {
    return sign_extend_val(((inst & 0xfe000000) >> 20) | ((inst & 0xf80) >> 7), 12);
}

uint32_t get_imm_btype(instruction_t inst) {
    return sign_extend_val(((inst & 0x80000000) >> 19) | ((inst & 0x7e000000) >> 20)
        | ((inst & 0xf00) >> 7) | ((inst & 0x80) << 4), 13);
}

uint32_t get_imm_utype(instruction_t inst) {
    return (inst & 0xfffff000);
}

uint32_t get_imm_jtype(instruction_t inst) {
    return sign_extend_val(((inst & 0x80000000) >> 11) | ((inst & 0x7fe00000) >> 20)
        | ((inst & 0x100000) >> 9) | (inst & 0xff000), 21);
}
