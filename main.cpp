#include "func.h"

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("The Mind", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font = TTF_OpenFont("DejaVuSans.ttf", 75);

    int frameTime = 0;
    Uint64 frameStart = 0;
    bool running = true;

    while(running) {
        frameStart = SDL_GetTicks64();
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT: {
                    running = false;
                    break;
                }
                case SDL_KEYDOWN: {
                    if(event.key.keysym.sym == SDLK_ESCAPE) {
                        running = selectionMenu(renderer, font, drawPause);
                    }
                    break;
                }
            }
        }
        
        SDL_SetRenderDrawColor(renderer,0,0,0,0);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        frameTime = SDL_GetTicks64() - frameStart;
        if(frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}