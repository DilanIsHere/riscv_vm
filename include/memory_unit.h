#ifndef MEMORY_UNIT_H
#define MEMORY_UNIT_H

#include <stdint.h>
#include "../include/instruction.h"

#define MEMORY_SIZE_IN_BYTES 51200

// Input values
extern uint32_t addr;
extern uint32_t writeData;
extern uint8_t memFlags;
extern BITSIZE dataLen;

// Flag for memory operation
typedef enum MEMFLAG {
    MEMFLAG_MEMWRITE = 1,
    MEMFLAG_MEMREAD  = 3,
    MEMFLAG_MEMTOREG = 5
} MEMFLAG;

#endif
