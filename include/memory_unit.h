#ifndef MEMORY_UNIT_H
#define MEMORY_UNIT_H


#include "../include/instruction.h"
#include "../include/utils.h"


#define MEMORY_SIZE_IN_BYTES 51200
#define BYTE_MASK 0xff


enum FLAG_ENUM CLOSED_ENUM MEM_FLAG_E: uint8_t {
    MEMFLAG_NOFLAGS  = 0,
    MEMFLAG_MEMWRITE = 1 << 0,
    MEMFLAG_MEMREAD  = 1 << 1,
    MEMFLAG_MEMTOREG = 1 << 2
};
// Flags for next memory operation
typedef enum MEM_FLAG_E MEM_FLAG;


// Operates on memory according to memFlags and input data
uint32_t operate_mem_unit(
    const uint32_t memAddr, uint32_t writeData, const MEM_FLAG memFlags,
    const DATA_LENGTH memLenInBytes
);


#endif
