#ifndef MEMORY_UNIT_H
#define MEMORY_UNIT_H

#include <stdint.h>
#include "../include/instruction.h"

#define MEMORY_SIZE_IN_BYTES 51200
#define BYTE_MASK 0xff

// Flag for memory operation
typedef enum MEM_FLAG {
    MEMFLAG_NOFLAGS  = 0,
    MEMFLAG_MEMWRITE = 1,
    MEMFLAG_MEMREAD  = 3,
    MEMFLAG_MEMTOREG = 5
} MEM_FLAG;

// Operates on memory according to memFlags and input data
uint32_t operate_mem_unit
    (const uint32_t memAddr, uint32_t writeData, const MEM_FLAG memFlags,
     const BYTE_LENGTH memLenInBytes);

#endif
