#ifndef CHIP8_REGISTERS_H
#define CHIP8_REGISTERS_H

#include <stdint.h>
#include "config.h"

typedef struct{
    uint16_t i_reg;
    uint16_t pc_reg;
    uint8_t v_reg[CHIP8_TOTAL_DATA_REGISTERS];
    uint8_t delay_timer_reg;
    uint8_t sound_timer_reg;
    uint8_t stack_pointer_reg;
}struct_chip8_registers_t;

#endif
