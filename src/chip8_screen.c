#include <assert.h>
#include <memory.h>

#include "chip8_screen.h"

/*
* Check if the row and coloumn are within the bounds of the screen.
*/
static void chip8_screen_check_bounds(uint8_t row, uint8_t coloumn)
{
    assert( (row < CHIP8_HEIGHT) && (coloumn < CHIP8_WIDTH) );
}

/*
* Set the pixel at the row and coloumn on the screen.
*/
void chip8_screen_set(struct_chip8_screen_t* system_screen, uint8_t row, uint8_t coloumn)
{
    chip8_screen_check_bounds(row, coloumn);
    system_screen->pixels[row][coloumn] = 1;
}

/*
* Check if the pixel at the row and coloumn is set.
*/
uint8_t chip8_screen_is_pixel_set(struct_chip8_screen_t* system_screen, uint8_t row, uint8_t coloumn)
{
    chip8_screen_check_bounds(row, coloumn);
    return system_screen->pixels[row][coloumn];
}

/*
* Clears the screen.
*/
void chip8_screen_clear(struct_chip8_screen_t* system_screen)
{
    memset(system_screen->pixels, 0, sizeof(system_screen->pixels));    // one of the things I learnned is that you can use memset on a 2d loop this way and pointer information is not decayed.
}

/*
* Draws a sprite on the screen at the row and coloumn.
* Returns 1 if there is a collision, 0 otherwise.
*/
uint8_t chip8_screen_draw_sprite(struct_chip8_screen_t* system_screen, uint8_t row, uint8_t coloumn, const uint8_t* sprite, uint8_t num_of_bytes)
{
    uint8_t pixel_collision = 0;
    uint8_t sprite_byte = 0;
    uint8_t mod_row = 0;
    uint8_t mod_coloumn = 0;

    for(uint8_t d_row = 0; d_row < num_of_bytes; d_row++)
    {
        sprite_byte = sprite[d_row];
        for(uint8_t d_coloumn = 0; d_coloumn < 8; d_coloumn++)
        {
            if( (sprite_byte & (0x80 >> d_coloumn)) == 0)
            {
                // do nothing
            }
            else
            {   
                mod_row = (row + d_row) % CHIP8_HEIGHT;
                mod_coloumn = (coloumn + d_coloumn) % CHIP8_WIDTH;
                if (system_screen->pixels[mod_row][mod_coloumn] == 1)
                {
                    pixel_collision = 1;
                }
                system_screen->pixels[mod_row][mod_coloumn] ^= 1;
            }
        }
    }
    
    return pixel_collision;
}