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
void chip8_exec(struct_chip8_t* chip8, uint16_t opcode);

#endif