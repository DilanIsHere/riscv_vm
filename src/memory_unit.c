#include <stdint.h>
#include "../include/memory_unit.h"


uint8_t mem_bank[MEMORY_SIZE_IN_BYTES];

uint32_t addr;
uint32_t writeData;
uint8_t memFlags;
BITSIZE dataLen;

void reset_mem_flags() {memFlags = 0;}

void set_mem_flag(MEMFLAG flag) {memFlags |= flag;}

