#include "func.h"

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("The Mind", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font = TTF_OpenFont("DejaVuSans.ttf", 75);

    int frameTime = 0, selection = -1;
    Uint64 frameStart = 0;
    bool running = true, beginning = true;

    while(running) {
        frameStart = SDL_GetTicks64();
        if(beginning) {
            selection = triMenu(renderer, font, drawHome);
            beginning = false;
        }
        else {
            switch(selection) {
                case 1: { //HOST
                    std::cout << "HOST" << std::endl;
                    beginning = true;
                    break;
                }
                case 2: { //JOIN
                    std::cout << "JOIN" << std::endl;
                    beginning = true;
                    break;
                }
                case 3: { //QUIT
                    running = false;
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