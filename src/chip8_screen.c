#include <assert.h>
#include "chip8_screen.h"

static void chip8_screen_check_bounds(uint8_t row, uint8_t coloumn)
{
    assert( (row < CHIP8_HEIGHT) && (coloumn < CHIP8_WIDTH) );
}

void chip8_screen_set(struct_chip8_screen_t* system_screen, uint8_t row, uint8_t coloumn)
{
    chip8_screen_check_bounds(row, coloumn);
    system_screen->pixels[row][coloumn] = 1;
}

uint8_t chip8_screen_is_pixel_set(struct_chip8_screen_t* system_screen, uint8_t row, uint8_t coloumn)
{
    chip8_screen_check_bounds(row, coloumn);
    return system_screen->pixels[row][coloumn];
}

void chip8_screen_clear(struct_chip8_screen_t* system_screen)
{
    for(uint8_t row = 0; row < CHIP8_HEIGHT; row++)
    {
        for(uint8_t coloumn = 0; coloumn < CHIP8_WIDTH; coloumn++)
        {
            system_screen->pixels[row][coloumn] = 0;
        }
    }
}