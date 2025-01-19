#include <memory.h>
#include <assert.h>
#include "chip8.h"

const uint8_t chip8_default_character_set[] =
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void chip8_init(struct_chip8_t* chip8)
{
    memset(chip8, 0, sizeof(struct_chip8_t) );
    memcpy(chip8->system_memory.memory, chip8_default_character_set, sizeof(chip8_default_character_set));
}
void chip8_load(struct_chip8_t* chip8, const uint8_t *buffer, size_t size)
{
    assert( (size + CHIP8_PROGRAM_LOAD_ADDR) < CHIP8_MEMORY_SIZE);
    memcpy(&chip8->system_memory.memory[CHIP8_PROGRAM_LOAD_ADDR], buffer, size);
    chip8->system_registers.pc_reg = CHIP8_PROGRAM_LOAD_ADDR;
}
void chip8_execute_opcode(struct_chip8_t* chip8, uint16_t opcode)
{
    switch(opcode)
    {
        /*
        * Clear the display.
        */
        case CHIP8_CLS:
            chip8_screen_clear(&(chip8->system_screen));
        break;

        /*
        * The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer.
        */
        case CHIP8_RET:
            chip8->system_registers.pc_reg = chip8_stack_pop(&chip8->system_stack, &chip8->system_registers.stack_pointer_reg);
        break;


        
    }
}
