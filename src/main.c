#include <stdio.h>
#include <SDL2/SDL.h>

#define UNUSED(x) (void)(x)

int main(int argc, char** argv) 
{
    UNUSED(argc);
    UNUSED(argv);
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow(
        "Hello, World!",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);
    while(1)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 0;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_Rect r;
        r.x =0;
        r.y =0;
        r.w = 40;
        r.h = 40;
        SDL_RenderDrawRect(renderer, &r);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    return 0;
}