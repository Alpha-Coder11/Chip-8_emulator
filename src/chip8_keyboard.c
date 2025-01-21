#include <assert.h>
#include "chip8_keyboard.h"

static void chip8_keyboard_key_in_bound (uint8_t key)
{
    assert(key < CHIP8_TOTAL_KEYS);
}

void chip8_keybaord_set_map(struct_chip8_keyboard_t* sys_keyboard,  const uint8_t* keyboard_map)
{
    sys_keyboard->keyboard_map = keyboard_map;
}

uint8_t chip8_keyboard_map(struct_chip8_keyboard_t* sys_keyboard, uint8_t key)
{
    uint8_t index = KEY_NOT_FOUND;
    for( index = 0; index < CHIP8_TOTAL_KEYS; index++)
    {
        if ( sys_keyboard->keyboard_map[index] == key )
        {
            break;
        }
    }
    return index;
}

void chip8_keyboard_key_down(struct_chip8_keyboard_t* keyboard, uint8_t key)
{
    chip8_keyboard_key_in_bound(key);
    keyboard->keyboard[key] = 1;
}
void chip8_keyboard_key_up(struct_chip8_keyboard_t* keyboard, uint8_t key)
{
    chip8_keyboard_key_in_bound(key);
    keyboard->keyboard[key] = 0;
}
uint8_t chip8_keyboard_is_key_down(struct_chip8_keyboard_t* keyboard, uint8_t key)
{
    chip8_keyboard_key_in_bound(key);
    return keyboard->keyboard[key]; 
}