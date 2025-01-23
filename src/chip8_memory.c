#include <assert.h>
#include "chip8_memory.h"
/*
* Check if the index is in bound of the memory
*/
static void chip8_memory_in_bound(uint32_t index)
{
    assert( index < CHIP8_MEMORY_SIZE );
}

/*
* Set the value at the index of the memory.
*/
void chip8_memory_set(struct_chip8_memory_t* sys_memory, uint32_t index, uint8_t value)
{
    chip8_memory_in_bound(index);
    sys_memory->memory[index] = value; 
}

/*
* Get the value at the index of the memory.
*/
uint8_t chip8_memory_get(struct_chip8_memory_t* sys_memory, uint32_t index)
{
    chip8_memory_in_bound(index);
    return sys_memory->memory[index];
}

/*
* Get the opcode at the index of the memory. Return the opcode as a 16 bit value.
*/
uint16_t chip8_memmory_get_opcode(struct_chip8_memory_t* sys_memory, uint32_t index)
{
    chip8_memory_in_bound(index + 1);
    uint8_t msb = sys_memory->memory[index];
    uint8_t lsb = sys_memory->memory[index + 1];
    return (msb << 8) | lsb;
}
