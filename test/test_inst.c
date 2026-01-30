/* Used for testing instruction module functions for correctness
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "../include/instruction.h"

#define ARR_LENGTH 4
#define HEX_BASE 16
#define BUFFER_SIZE 9
#define WORD_LEN_IN_BITS 32

void output_test_results(bool result, char *functionName);

int main(int argc, char** argv) {
    assert(argc > 1 && "Requires arguments for testing\n");
    uint8_t littleEndianWord[ARR_LENGTH];
    for (size_t i = 0; i < ARR_LENGTH; i++) {
        littleEndianWord[i] = (uint8_t)strtoul(argv[i+1], NULL, HEX_BASE);
    }

    char output[BUFFER_SIZE];
    instruction_t inst = convert_word_to_inst(littleEndianWord);
    snprintf(output, BUFFER_SIZE, "%8x", inst);

    // Checks that convert_word_to_inst follows little-endian format
    output_test_results(strcmp(argv[5], output) == 0, "convert_word_to_inst");


    int bitLength = atoi(argv[6]);
    uint32_t testExtend = inst >> (WORD_LEN_IN_BITS - bitLength);
    testExtend = sign_extend_val(testExtend, bitLength);
    uint32_t checkExtend = strtoul(argv[7], NULL, HEX_BASE);

    // Checks that sign_extend_val sign-extends properly
    output_test_results(testExtend == checkExtend, "sign_extend_val");

    // Checks opcode function
    OPCODE testOp = (OPCODE)strtoul(argv[8], NULL, HEX_BASE);
    output_test_results(testOp == get_opcode(inst), "get_opcode");

    // Checks various value-fetch functions
    uint8_t testVal = strtoul(argv[9], NULL, HEX_BASE);
    output_test_results(testVal == get_rd(inst), "get_rd");
    testVal = strtoul(argv[10], NULL, HEX_BASE);
    output_test_results(testVal == get_funct3(inst), "get_funct3");
    testVal = strtoul(argv[11], NULL, HEX_BASE);
    output_test_results(testVal == get_rs1(inst), "get_rs1");
    testVal = strtoul(argv[12], NULL, HEX_BASE);
    output_test_results(testVal == get_rs2(inst), "get_rs2");
    testVal = strtoul(argv[13], NULL, HEX_BASE);
    output_test_results(testVal == get_funct7(inst), "get_funct7");

    uint32_t immTest = strtoul(argv[14], NULL, HEX_BASE);
    output_test_results(immTest == get_imm_itype(inst), "get_imm_itype");
    immTest = strtoul(argv[15], NULL, HEX_BASE);
    output_test_results(immTest == get_imm_stype(inst), "get_imm_stype");
    immTest = strtoul(argv[16], NULL, HEX_BASE);
    output_test_results(immTest == get_imm_btype(inst), "get_imm_btype");
    immTest = strtoul(argv[17], NULL, HEX_BASE);
    output_test_results(immTest == get_imm_utype(inst), "get_imm_utype");
    immTest = strtoul(argv[18], NULL, HEX_BASE);
    output_test_results(immTest == get_imm_jtype(inst), "get_imm_jtype");
}

void output_test_results(bool result, char *functionName) {
    if (result) {
        printf("TEST PASSED: %s\n", functionName);
    }
    else {
        printf("TEST FAILED: %s\n", functionName);
        exit(EXIT_FAILURE);
    }
}
