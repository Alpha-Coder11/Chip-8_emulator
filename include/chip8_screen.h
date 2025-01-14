#ifndef CHIP8_SCREEN_H
#define CHIP8_SCREEN_H

#include <stdint.h>
#include "config.h"

typedef struct
{
    uint8_t pixels[CHIP8_HEIGHT][CHIP8_WIDTH];
} struct_chip8_screen_t;

void chip8_screen_set(struct_chip8_screen_t* system_screen, uint8_t row, uint8_t coloumn);
uint8_t chip8_screen_is_pixel_set(struct_chip8_screen_t* system_screen, uint8_t row, uint8_t coloumn);
void chip8_screen_clear(struct_chip8_screen_t* system_screen);

#endif
