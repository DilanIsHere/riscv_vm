/* Requires additional functions for initial instruction loading into memAddr
 * Will add after input file format determined
 */

#include "../include/memory_unit.h"

// VM memory bank
static uint8_t memBank[MEMORY_SIZE_IN_BYTES];

// Saves writeData in memBank
static void set_mem_data(
    const uint32_t memAddr, uint32_t writeData, const DATA_LENGTH memLenInBytes
) {
    if (memAddr + memLenInBytes >= MEMORY_SIZE_IN_BYTES) {
        fatal_error(ERR_OUT_OF_BOUNDS);
    }

    for (int i = memLenInBytes - 1; i >= 0; i--) {
        memBank[memAddr + i] = writeData & BYTE_MASK;
        writeData >>= LENGTH_BYTE_IN_BITS;
    }
}

// Reads and returns data from memBank
static uint32_t get_mem_data(
    const uint32_t memAddr, const DATA_LENGTH memLenInBytes
) {
    if (memAddr + memLenInBytes >= MEMORY_SIZE_IN_BYTES) {
        fatal_error(ERR_OUT_OF_BOUNDS);
    }

    uint32_t readData = 0;

    for (int i = 0; i < memLenInBytes; i++) {
        readData <<= LENGTH_BYTE_IN_BITS;
        readData |= memBank[memAddr + i];
    }
    return readData;
}

uint32_t operate_mem_unit(
    const uint32_t memAddr, uint32_t writeData, const MEM_FLAG memFlags,
    const DATA_LENGTH memLenInBytes
) {
    if ((memFlags & MEMFLAG_MEMREAD) == MEMFLAG_MEMREAD
        && (memFlags & MEMFLAG_MEMWRITE) == MEMFLAG_MEMWRITE)
    {
        fatal_error(ERR_ILLEGAL_VALUE);
    }

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
