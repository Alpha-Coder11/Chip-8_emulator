#ifndef CHIP8_H
#define CHIP8_H

#include "config.h"
#include "chip8_memory.h"
#include "chip8_registers.h"

typedef struct{
    struct_chip8_memory_t system_memory;
    struct_chip8_registers_t system_registers;
} struct_chip8_t;

#endif