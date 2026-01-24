/* Used for testing instruction module functions for correctness
 */

#include <stdio.h>
#include "../include/instruction.h"

int main() {
    // convert_word_to_inst
    uint8_t word[4] = {0x4a, 0x51, 0x01, 0x9f};
    instruction_t inst = convert_word_to_inst(word);
    printf("Expected:\t");
    for (int i = 3; i >= 0; i++) {
        printf("%x", word[i]);
    }
    printf("\nActual:\t%x\n", inst);
}
