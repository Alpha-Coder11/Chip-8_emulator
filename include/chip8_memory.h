#ifndef CHIP8_MEMORY_H
#define CHIP8_MEMORY_H

#include <stdint.h>
#include "config.h"

typedef struct{
    char memory[CHIP8_MEMORY_SIZE];
} struct_chip8_memory_t;

void chip8_memory_set(struct_chip8_memory_t* sys_memory, uint32_t index, uint8_t value);
uint8_t chipt8_memory_get(struct_chip8_memory_t* sys_memory, uint32_t index);

#endif