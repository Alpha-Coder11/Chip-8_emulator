#ifndef CHIP8_STACK_H
#define CHIP8_STACK_H

#include <stdint.h>
#include "config.h"


typedef struct{
    uint16_t stack[CHIP8_STACK_SIZE];
} struct_chip8_stack_t;

void chip8_stack_push( struct_chip8_stack_t* system_stack, uint8_t* stack_pointer_reg , uint16_t value);
uint16_t chip8_stack_pop( struct_chip8_stack_t* system_stack, uint8_t* stack_pointer_reg);

#endif