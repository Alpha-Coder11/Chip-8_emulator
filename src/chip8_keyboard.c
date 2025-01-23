#include <assert.h>
#include "chip8_keyboard.h"
/*
* Check if the key is in bound.
*/
static void chip8_keyboard_key_in_bound (uint8_t key)
{
    assert(key < CHIP8_TOTAL_KEYS);
}


void chip8_keybaord_set_map(struct_chip8_keyboard_t* sys_keyboard,  const uint8_t* keyboard_map)
{
    sys_keyboard->keyboard_map = keyboard_map;
}

/*
* It makes an map of keys available to the emulator to the keys available in the keyboard.
* If the key is not found, it returns KEY_NOT_FOUND.
*/
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
/*
* Set the key to down.
*/
void chip8_keyboard_key_down(struct_chip8_keyboard_t* keyboard, uint8_t key)
{
    chip8_keyboard_key_in_bound(key);
    keyboard->keyboard[key] = 1;
}

/*
* Set the key to up.
*/
void chip8_keyboard_key_up(struct_chip8_keyboard_t* keyboard, uint8_t key)
{
    chip8_keyboard_key_in_bound(key);
    keyboard->keyboard[key] = 0;
}

/*
* Checks if the key is down.
* Return 1 if the key is down, 0 otherwise.
*/
uint8_t chip8_keyboard_is_key_down(struct_chip8_keyboard_t* keyboard, uint8_t key)
{
    chip8_keyboard_key_in_bound(key);
    return keyboard->keyboard[key]; 
}