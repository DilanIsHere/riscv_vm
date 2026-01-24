/* Requires additional functions for initial instruction loading into memAddr
 * Will add after input file format determined
 */

#include "../include/memory_unit.h"
#include <assert.h>

// VM memory bank
static uint8_t memBank[MEMORY_SIZE_IN_BYTES];

// Saves writeData in memBank
static void set_mem_data
    (const uint32_t memAddr, uint32_t writeData, const BYTE_LENGTH memLenInBytes)
{
    assert(memAddr + memLenInBytes <= MEMORY_SIZE_IN_BYTES);

    for (int i = memLenInBytes - 1; i >= 0; i--) {
        memBank[memAddr + i] = writeData & BYTE_MASK;
        writeData >>= BITSIZE_BYTE;
    }
}

// Reads and returns data from memBank
static uint32_t get_mem_data
    (const uint32_t memAddr, const BYTE_LENGTH memLenInBytes)
{
    assert(memAddr + memLenInBytes <= MEMORY_SIZE_IN_BYTES);

    uint32_t readData = 0;

    for (int i = 0; i < memLenInBytes; i++) {
        readData <<= BITSIZE_BYTE;
        readData |= memBank[memAddr + i];
    }
    return readData;
}

uint32_t operate_mem_unit
    (const uint32_t memAddr, uint32_t writeData, const MEM_FLAG memFlags,
     const BYTE_LENGTH memLenInBytes)
{
    assert((memFlags & MEMFLAG_MEMREAD) == MEMFLAG_MEMREAD
        && (memFlags & MEMFLAG_MEMWRITE) == MEMFLAG_MEMWRITE);

    uint32_t readData = 0;
    if ((memFlags & MEMFLAG_MEMREAD) == MEMFLAG_MEMREAD) {
        readData = get_mem_data(memAddr, memLenInBytes);
    }
    else if ((memFlags & MEMFLAG_MEMWRITE) == MEMFLAG_MEMWRITE) {
        set_mem_data(memAddr, writeData, memLenInBytes);
    }

    if ((memFlags & MEMFLAG_MEMTOREG) == MEMFLAG_MEMTOREG) {
        return readData;
    }
    return memAddr;
}
