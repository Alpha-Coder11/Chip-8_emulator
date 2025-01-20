#ifndef CHIP8_H
#define CHIP8_H

#include <stddef.h>

#include "config.h"
#include "chip8_memory.h"
#include "chip8_registers.h"
#include "chip8_stack.h"
#include "chip8_keyboard.h"
#include "chip8_screen.h"

typedef struct{
    struct_chip8_memory_t system_memory;
    struct_chip8_registers_t system_registers;
    struct_chip8_stack_t system_stack;
    struct_chip8_keyboard_t system_keyboard;
    struct_chip8_screen_t system_screen;
} struct_chip8_t;

void chip8_init(struct_chip8_t* chip8);
void chip8_load(struct_chip8_t* chip8, const uint8_t *buffer, size_t size);
void chip8_execute_opcode(struct_chip8_t* chip8, uint16_t opcode);

#define CHIP8_CLS  0x00E0    ///< Clears the display
#define CHIP8_RET  0x00EE    ///< Returns from a subroutine
#define CHIP8_JP   0x1000    ///< Jumps to address NNN, format 0x1NNN
#define CHIP8_CALL 0x2000    ///< Calls subroutine at NNN, format 0x2NNN
#define CHIP8_SE   0x3000    ///< Skips the next instruction if VX equals NN, format 0x3XNN
#define CHIP8_SNE  0x4000    ///< Skips the next instruction if VX doesn't equal NN, format 0x4XNN
#define CHIP8_SE2  0x5000    ///< Skips the next instruction if VX equals VY, format 0x5XY0
#define CHIP8_LD   0x6000    ///< Sets VX to NN, format 0x6XNN
#define CHIP8_ADD  0x7000    ///< Adds NN to VX, format 0x7XNN
#define CHIP8_LD2  0x8000    ///< Sets VX to the value of VY, format 0x8XY0
#define CHIP8_OR   0x8001    ///< Sets VX to VX or VY, format 0x8XY1
#define CHIP8_AND  0x8002    ///< Sets VX to VX and VY, format 0x8XY2
#define CHIP8_XOR  0x8003    ///< Sets VX to VX xor VY, format 0x8XY3
#define CHIP8_ADD2 0x8004    ///< Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't, format 0x8XY4
#define CHIP8_SUB  0x8005    ///< VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't, format 0x8XY5
#define CHIP8_SHR  0x8006    ///< Shifts VX right by one. VF is set to the value of the least significant bit of VX before the shift, format 0x8XY6
#define CHIP8_SUBN 0x8007    ///< Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't, format 0x8XY7
#define CHIP8_SHL  0x800E    ///< Shifts VX left by one. VF is set to the value of the most significant bit of VX before the shift, format 0x8XYE
#define CHIP8_SNE2 0x9000    ///< Skips the next instruction if VX doesn't equal VY, format 0x9XY0
#define CHIP8_LD3  0xA000    ///< Sets Register I to the address NNN, format 0xANNN
#define CHIP8_JP2  0xB000    ///< Jumps to the address location NNN plus V0, format 0xBNNN
#define CHIP8_RND  0xC000    ///< Sets VX to the result of a bitwise AND operation on a random number and NN, format 0xCXNN
#define CHIP8_DRW  0xD000    ///< Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels, format 0xDXYN

#define CHIP8_E   0xE000
#define CHIP8_SKP  0xE09E    ///< Skips the next instruction if the key stored in VX is pressed, format 0xEX9E
#define CHIP8_SKNP 0xE0A1    ///< Skips the next instruction if the key stored in VX isn't pressed, format 0xEXA1

#define CHIP8_F    0xF000
#define CHIP8_LD4  0xF007    ///< Sets VX to the value of the delay timer, format 0xFX07
#define CHIP8_LD5  0xF00A    ///< A key press is awaited, and then stored in VX, format 0xFX0A
#define CHIP8_LD6  0xF015    ///< Sets the delay timer to VX, format 0xFX15
#define CHIP8_LD7  0xF018    ///< Sets the sound timer to VX, format 0xFX18
#define CHIP8_ADD3 0xF01E    ///< Adds VX to I, format 0xFX1E
#define CHIP8_LD8  0xF029    ///< Sets I to the location of the sprite for the character in VX, format 0xFX29
#define CHIP8_LD9  0xF033    ///< Stores the BCD representation of Vx in memory locations I, I+1, and I+2, format 0xFX33
#define CHIP8_LD10 0xF055    ///< Stores V0 to VX in memory starting at address I, format 0xFX55 //TODO understand this
#define CHIP8_LD11 0xF065    ///< Fills V0 to VX with values from memory starting at address I, format 0xFX65 //TODO understand this

#define GET_INSTRUCTION(opcode)      (opcode & 0xf000)
#define GET_INSTRUCTION_8(opcode)    (opcode & 0xf00f)
#define GET_INSTRUCTION_E(opcode)    (opcode & 0xF0FF)
#define GET_INSTRUCTION_F(opcode)    (opcode & 0xF0FF)
#define GET_PROGRAM_COUNTER(opcode)  (opcode & 0x0FFF)
#define GET_X_VALUE(opcode)          ((opcode >> 8) & 0x000F)
#define GET_Y_VALUE(opcode)          ((opcode >> 4) & 0x000F)
#define GET_KK_VALUE(opcode)         ( opcode & 0x00FF)
#define GET_NNN_VALUE(opcode)        (opcode & 0x0FFF)
#define GET_N_VALUE(opcode)          (opcode & 0x000F)

#endif