#ifndef CHIP8_KEYBOARD_H
#define CHIP8_KEYBOARD_H

#include <stdint.h>
#include "config.h"

#define KEY_NOT_FOUND 0xFF

typedef struct{
    uint8_t keyboard[CHIP8_TOTAL_KEYS];
    const uint8_t* keyboard_map;

} struct_chip8_keyboard_t;

uint8_t chip8_keyboard_map(struct_chip8_keyboard_t* sys_keyboard, uint8_t key);
void chip8_keyboard_key_down(struct_chip8_keyboard_t* keyboard, uint8_t key);
void chip8_keyboard_key_up(struct_chip8_keyboard_t* keyboard, uint8_t key);
uint8_t chip8_keyboard_is_key_down(struct_chip8_keyboard_t* keyboard, uint8_t key);
void chip8_keybaord_set_map(struct_chip8_keyboard_t* sys_keyboard,  const uint8_t* keyboard_map);

#endif