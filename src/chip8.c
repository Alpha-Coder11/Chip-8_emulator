#include <memory.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "SDL2/SDL.h"

#include "chip8.h"

const uint8_t chip8_default_character_set[] =
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

static void chip8_execute_command_8000(struct_chip8_t* chip8, uint16_t opcode)
{
    uint16_t instruction = GET_INSTRUCTION_8(opcode);
    uint16_t temp = 0;
    switch(instruction)
    {
        case CHIP8_LD2:
            chip8->system_registers.v_reg[GET_X_VALUE(opcode)] = chip8->system_registers.v_reg[GET_Y_VALUE(opcode)];
        break;

        case CHIP8_OR:
            chip8->system_registers.v_reg[GET_X_VALUE(opcode)] |= chip8->system_registers.v_reg[GET_Y_VALUE(opcode)];
        break;

        case CHIP8_AND:
            chip8->system_registers.v_reg[GET_X_VALUE(opcode)] &= chip8->system_registers.v_reg[GET_Y_VALUE(opcode)];
        break;

        case CHIP8_XOR:
            chip8->system_registers.v_reg[GET_X_VALUE(opcode)] ^= chip8->system_registers.v_reg[GET_Y_VALUE(opcode)];
        break;

        case CHIP8_ADD2:
            temp = chip8->system_registers.v_reg[GET_X_VALUE(opcode)] + chip8->system_registers.v_reg[GET_Y_VALUE(opcode)]; 
            chip8->system_registers.v_reg[GET_X_VALUE(opcode)] += chip8->system_registers.v_reg[GET_Y_VALUE(opcode)];
            if (temp > 255)
            {
                chip8->system_registers.v_reg[0x0F] = 1;
            }
            else
            {
                chip8->system_registers.v_reg[0x0F] = 0;
            }
        break;

        case CHIP8_SUB:
            if ( chip8->system_registers.v_reg[GET_X_VALUE(opcode)] > chip8->system_registers.v_reg[GET_Y_VALUE(opcode)] )
            {
                chip8->system_registers.v_reg[GET_X_VALUE(opcode)] = chip8->system_registers.v_reg[GET_X_VALUE(opcode)] - chip8->system_registers.v_reg[GET_Y_VALUE(opcode)];
                chip8->system_registers.v_reg[0x0F] = 1;
            }
            else
            {
                // chip8->system_registers.v_reg[GET_X_VALUE(opcode)] = chip8->system_registers.v_reg[GET_Y_VALUE(opcode)] - chip8->system_registers.v_reg[GET_X_VALUE(opcode)];
                chip8->system_registers.v_reg[0x0F] = 0;
            }
        break;

        case CHIP8_SHR:
            
            chip8->system_registers.v_reg[0x0F] = chip8->system_registers.v_reg[GET_X_VALUE(opcode)] & 0x0001;
            chip8->system_registers.v_reg[GET_X_VALUE(opcode)] = (chip8->system_registers.v_reg[GET_X_VALUE(opcode)]) >> 1;

        
        break;

        case CHIP8_SUBN:
            chip8->system_registers.v_reg[0x0F] = chip8->system_registers.v_reg[GET_Y_VALUE(opcode)] > chip8->system_registers.v_reg[GET_X_VALUE(opcode)]; 
            chip8->system_registers.v_reg[GET_X_VALUE(opcode)] = chip8->system_registers.v_reg[GET_Y_VALUE(opcode)] - chip8->system_registers.v_reg[GET_X_VALUE(opcode)];
                
        break;

        case CHIP8_SHL:
            chip8->system_registers.v_reg[0x0F] = (chip8->system_registers.v_reg[GET_X_VALUE(opcode)] & 0x80) >> 7;
            chip8->system_registers.v_reg[GET_X_VALUE(opcode)] = chip8->system_registers.v_reg[GET_X_VALUE(opcode)] << 1;

        break;
    }
}

void chip8_execute_command_E000(struct_chip8_t* chip8, uint16_t opcode)
{
    uint16_t instruction = GET_INSTRUCTION_E(opcode);
    switch (instruction)
    {
        case CHIP8_SKP: 
            if( chip8_keyboard_is_key_down(&chip8->system_keyboard, chip8->system_registers.v_reg[GET_X_VALUE(opcode)]) )
            {
                chip8->system_registers.pc_reg += 2;
            }
        break;

        case CHIP8_SKNP: 
            if( !chip8_keyboard_is_key_down(&chip8->system_keyboard, chip8->system_registers.v_reg[GET_X_VALUE(opcode)]) )
            {
                chip8->system_registers.pc_reg += 2;
            }
        break;

    }
}
static uint8_t chip8_wait_for_key_press(struct_chip8_t* chip8)
{
    SDL_Event event;
    while(SDL_WaitEvent(&event))
    {
        if ( event.type != SDL_KEYDOWN )
        {
            // do nothing
        }
        else
        {
            uint8_t key = event.key.keysym.sym;
            uint8_t chip8_key = chip8_keyboard_map(&chip8->system_keyboard, key);
            if(chip8_key != CHIP8_TOTAL_KEYS)
            {
                return chip8_key;
            }
        }
    }
    return CHIP8_TOTAL_KEYS;
}

void chip8_execute_command_F000(struct_chip8_t* chip8, uint16_t opcode)
{
    uint16_t instruction = GET_INSTRUCTION_F(opcode);
    switch (instruction)
    {
        case CHIP8_LD4 :
            chip8->system_registers.v_reg[GET_X_VALUE(opcode)] = chip8->system_registers.delay_timer_reg;
        break;

        case CHIP8_LD5 :
        {
            uint8_t pressed_key = chip8_wait_for_key_press(chip8);
            chip8->system_registers.v_reg[GET_X_VALUE(opcode)] = pressed_key;
        }
        break;
        
        case CHIP8_LD6 :
            chip8->system_registers.delay_timer_reg = chip8->system_registers.v_reg[GET_X_VALUE(opcode)];

        break;
        case CHIP8_LD7 :
            chip8->system_registers.sound_timer_reg = chip8->system_registers.v_reg[GET_X_VALUE(opcode)];
        break;
        case CHIP8_ADD3:
            chip8->system_registers.i_reg += chip8->system_registers.v_reg[GET_X_VALUE(opcode)];
        break;
        case CHIP8_LD8 :
            chip8->system_registers.i_reg = chip8->system_registers.v_reg[GET_X_VALUE(opcode)] * CHIP8_HRIGHT_OF_SPRITE;
        break;
        case CHIP8_LD9 :
        {

            uint8_t hundreth = chip8->system_registers.v_reg[GET_X_VALUE(opcode)] % 100;
            uint8_t tenths =  (chip8->system_registers.v_reg[GET_X_VALUE(opcode)] /10) % 10; 
            uint8_t unit = chip8->system_registers.v_reg[GET_X_VALUE(opcode)] % 10; 

            chip8_memory_set(&chip8->system_memory, chip8->system_registers.i_reg, hundreth);
            chip8_memory_set(&chip8->system_memory, chip8->system_registers.i_reg + 1, tenths);
            chip8_memory_set(&chip8->system_memory, chip8->system_registers.i_reg + 2, unit);
        }
        break;
        case CHIP8_LD10:
        {

            for(uint8_t index = 0; index <= GET_X_VALUE(opcode); index++)
            {
                chip8_memory_set(&chip8->system_memory, chip8->system_registers.i_reg + index, chip8->system_registers.v_reg[index]);
            }
        }
        break;
        case CHIP8_LD11:
        {

            for(uint8_t index = 0; index <= GET_X_VALUE(opcode); index++)
            {
                chip8->system_registers.v_reg[index] = chip8_memory_get(&chip8->system_memory, chip8->system_registers.i_reg + index);
            }
        }

        break;
    }
}

static void chip8_extended_command(struct_chip8_t* chip8, uint16_t opcode)
{
    uint16_t instruction = GET_INSTRUCTION(opcode);
    switch (instruction)
    {
        /*
        * Jump to location nnn.
        */
        case CHIP8_JP:
            chip8->system_registers.pc_reg = GET_PROGRAM_COUNTER(opcode);
        break;

        case CHIP8_CALL:
            chip8_stack_push(&chip8->system_stack, &chip8->system_registers.stack_pointer_reg, chip8->system_registers.pc_reg );
            chip8->system_registers.pc_reg = GET_PROGRAM_COUNTER(opcode);
        break;

        /*
        * Skip next instruction if Vx = kk.
        */
        case CHIP8_SE:
            if ( chip8->system_registers.v_reg[GET_X_VALUE(opcode)] == GET_KK_VALUE(opcode) )
            {
                chip8->system_registers.pc_reg += 2;
            } 
            else
            {
                // do nothing 
            }
        break;

        /*
        * Skip next instruction if Vx != kk.
        */
        case CHIP8_SNE:
            if ( chip8->system_registers.v_reg[GET_X_VALUE(opcode)] != GET_KK_VALUE(opcode) )
            {
                chip8->system_registers.pc_reg += 2;
            } 
            else
            {
                // do nothing 
            }            

        break;

        /*
        * Skip next instruction if Vx = Vy.
        */
        case CHIP8_SE2:
            if ( chip8->system_registers.v_reg[GET_X_VALUE(opcode)] == chip8->system_registers.v_reg[GET_Y_VALUE(opcode)] )
            {
                chip8->system_registers.pc_reg += 2;
            } 
            else
            {
                // do nothing 
            }      
        break;

        /*
        * Set Vx = kk.
        */
        case CHIP8_LD:
            chip8->system_registers.v_reg[GET_X_VALUE(opcode)] = GET_KK_VALUE(opcode); 
        break;
        /*
        * Set Vx = Vx + kk.
        */
        case CHIP8_ADD:
             chip8->system_registers.v_reg[GET_X_VALUE(opcode)] += GET_KK_VALUE(opcode);
        break; 

        case CHIP8_LD2:
            chip8_execute_command_8000(chip8, opcode);
        break;

        // skips next instruction if Vx!=Vy
        case CHIP8_SNE2:
            if( chip8->system_registers.v_reg[GET_X_VALUE(opcode)] != chip8->system_registers.v_reg[GET_Y_VALUE(opcode)])
            {
                chip8->system_registers.pc_reg += 2;
            }
        break;
        case CHIP8_LD3 :
            chip8->system_registers.i_reg = GET_NNN_VALUE(opcode);
        break;

        case CHIP8_JP2:
            chip8->system_registers.pc_reg =  GET_NNN_VALUE(opcode) + chip8->system_registers.v_reg[0x00];
        break;

        case CHIP8_RND:
            srand(clock());
             chip8->system_registers.v_reg[GET_X_VALUE(opcode)] = (rand() % 255) & GET_KK_VALUE(opcode);
        break;

        case CHIP8_DRW:
        {  
            const uint8_t* sprite = (const uint8_t* )&chip8->system_memory.memory[chip8->system_registers.i_reg];
            chip8->system_registers.v_reg[0x0F] = chip8_screen_draw_sprite(&chip8->system_screen, chip8->system_registers.v_reg[GET_Y_VALUE(opcode)], chip8->system_registers.v_reg[GET_X_VALUE(opcode)], sprite, GET_N_VALUE(opcode));
        }

        case CHIP8_E: 
            chip8_execute_command_E000(chip8, opcode);
        break;

        case CHIP8_F: 
            chip8_execute_command_F000(chip8, opcode);
        break;
    }
}

void chip8_init(struct_chip8_t* chip8)
{
    memset(chip8, 0, sizeof(struct_chip8_t) );
    memcpy(chip8->system_memory.memory, chip8_default_character_set, sizeof(chip8_default_character_set));
}
void chip8_load(struct_chip8_t* chip8, const uint8_t *buffer, size_t size)
{
    assert( (size + CHIP8_PROGRAM_LOAD_ADDR) < CHIP8_MEMORY_SIZE);
    memcpy(&chip8->system_memory.memory[CHIP8_PROGRAM_LOAD_ADDR], buffer, size);
    chip8->system_registers.pc_reg = CHIP8_PROGRAM_LOAD_ADDR;
}
void chip8_execute_opcode(struct_chip8_t* chip8, uint16_t opcode)
{
    switch(opcode)
    {
        /*
        * Clear the display.
        */
        case CHIP8_CLS:
            chip8_screen_clear(&chip8->system_screen);
        break;

        /*
        * The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer.
        */
        case CHIP8_RET:
            chip8->system_registers.pc_reg = chip8_stack_pop(&chip8->system_stack, &chip8->system_registers.stack_pointer_reg);
        break;

        default:
            chip8_extended_command(chip8, opcode);
        break;        
    }
}
