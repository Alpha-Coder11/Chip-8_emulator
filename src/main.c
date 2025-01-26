#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "config.h"
#include "chip8.h"

const uint8_t keyboard[] =
{
    SDLK_1, SDLK_2, SDLK_3, SDLK_4,
    SDLK_q, SDLK_w, SDLK_e, SDLK_r,
    SDLK_a, SDLK_s, SDLK_d, SDLK_f,
    SDLK_z, SDLK_x, SDLK_c, SDLK_v
};

int main(int argc, char** argv) 
{
    uint8_t buffer[CHIP8_MEMORY_SIZE - CHIP8_PROGRAM_LOAD_ADDR] = {};
    uint16_t opcode = 0;

    if ( argc < 2 )
    {
        printf("You must provide a ROM File\n");
        return 0;
    }
    const char *filename = argv[1];
    printf("The file to load is %s\n", filename);
    FILE *ROM = fopen(filename, "rb");  // we use the mode rb instead of just r because we want the operating system to treat the file as binary
    if (ROM == NULL)
    {
        printf("Error: Could not open file %s\n", filename);
        return 0;
    }
    fseek(ROM, 0, SEEK_END);
    uint32_t size = ftell(ROM);     // tells the position of the file pointer
    fseek(ROM, 0 , SEEK_SET);       // sets the file pointer to the beginning of the file
    uint32_t ret = fread(buffer, size, 1, ROM);
    if ( ret != 1 ) 
    {
        fclose(ROM);
        printf("Failed to read from file\n");
        return 0;
    }

    struct_chip8_t chip8 = {0};
    chip8_init(&chip8);
    chip8_load(&chip8, buffer, size);
    chip8_keybaord_set_map(&chip8.system_keyboard, keyboard);


    uint8_t key = 0xFF;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow(
        EMULATOR_WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        CHIP8_WIDTH * EMULATOR_WINDOW_SCALE,
        CHIP8_HEIGHT * EMULATOR_WINDOW_SCALE,
        SDL_WINDOW_SHOWN
    );

    chip8.system_registers.delay_timer_reg = 0;
    chip8.system_registers.sound_timer_reg = 0;

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);
    while(1)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    key = event.key.keysym.sym;
                    key = chip8_keyboard_map(&chip8.system_keyboard, key); 
                    if ( key != CHIP8_TOTAL_KEYS )
                    {
                        chip8_keyboard_key_down(&chip8.system_keyboard, key);
                    }
                    
                break;

                case SDL_KEYUP:
                    key = event.key.keysym.sym;
                    key = chip8_keyboard_map(&chip8.system_keyboard, key); 
                    if ( key != CHIP8_TOTAL_KEYS )
                    {
                        chip8_keyboard_key_up(&chip8.system_keyboard, key);
                    }
                break;
                
                case SDL_QUIT:
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                    return 0;
                break;

            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

        for(uint8_t row = 0; row < CHIP8_HEIGHT; row++)
        {
            for(uint8_t coloumn = 0; coloumn < CHIP8_WIDTH; coloumn++)
            {
                if ( chip8.system_screen.pixels[row][coloumn] == 1 )
                {
                    SDL_Rect r;
                    r.x = coloumn * EMULATOR_WINDOW_SCALE;
                    r.y = row * EMULATOR_WINDOW_SCALE;
                    r.w = EMULATOR_WINDOW_SCALE;
                    r.h = EMULATOR_WINDOW_SCALE;
                    SDL_RenderFillRect(renderer, &r);
                }
            }
        }

        SDL_RenderPresent(renderer);
        if ( chip8.system_registers.delay_timer_reg > 0 )
        {
            SDL_Delay(1);
            chip8.system_registers.delay_timer_reg--;
        }
        if ( chip8.system_registers.sound_timer_reg > 0 )
        {
            //TODO find the beeper alternative for linux
            // Beep(13000, 10 * chip8.system_registers.sound_timer_reg);
            chip8.system_registers.sound_timer_reg = 0;
        }
        opcode = chip8_memmory_get_opcode(&chip8.system_memory, chip8.system_registers.pc_reg);
        chip8.system_registers.pc_reg += CHIP8_SIZE_OF_INSTRUCTION;
        chip8_execute_opcode(&chip8, opcode);
    }   
    SDL_DestroyWindow(window);
    return 0;
}