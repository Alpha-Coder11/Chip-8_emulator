#include <memory.h>
#include "chip8.h"

void chip8_init(struct_chip8_t* chip8)
{
    memset(chip8, 0, sizeof(struct_chip8_t) );
}
