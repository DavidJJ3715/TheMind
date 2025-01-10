#ifndef _func_
#define _func_
#define SDL_MAIN_HANDLED
#include <algorithm>
#include <chrono>
#include <climits>
#include <cmath>
#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <vector>
#include "../SDL2/include/SDL2/SDL.h"
#include "../SDL2/include/SDL2/SDL_ttf.h"
#include "../SDL2/include/SDL2/SDL_image.h"

/********************************
*       Global Variables        *
*********************************/
const int WIDTH = 1200, HEIGHT = 800, frameDelay = 4;

/********************************
*       Server Functions        *
*********************************/

/********************************
*       Core Functionality      *
*********************************/

/********************************
*       Draw Functions          *
*********************************/
void drawHome(SDL_Renderer* renderer, TTF_Font* font, int selection) {
    int menuWidth = (WIDTH/2), menuHeight = 3*(HEIGHT/4); //Bounds of the text box
    int widthVal = (WIDTH/2)-145, heightVal = -1;
    SDL_Rect border;

    SDL_Surface* surface = TTF_RenderText_Solid(font, "THE MIND", {255,255,255,0}); //Game pause text
    SDL_Texture* titleText = SDL_CreateTextureFromSurface(renderer, surface); //Make it a texture
    SDL_FreeSurface(surface); //Free the surface to prevent memory leaks
    surface = TTF_RenderText_Solid(font, "HOST", {255,255,255,0}); //Server text
    SDL_Texture* hostText = SDL_CreateTextureFromSurface(renderer, surface); //Make it a texture
    SDL_FreeSurface(surface); 
    surface = TTF_RenderText_Solid(font, "JOIN", {255,255,255,0}); //Client text
    SDL_Texture* joinText = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); 
    surface = TTF_RenderText_Solid(font, "QUIT", {255,255,255,0}); //Quit text
    SDL_Texture* quitText = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); 

    SDL_Rect title = {(WIDTH/2)-200, (HEIGHT/2)-(menuHeight/2)+25, 400, 140}; //Location of "THE MIND"
    SDL_Rect host = {(WIDTH/2)-100, (HEIGHT/2)-125, 200, 100}; //Location of "HOST"
    SDL_Rect join = {(WIDTH/2)-100, (HEIGHT/2)+25, 200, 100}; //Location of "JOIN"
    SDL_Rect quit = {(WIDTH/2)-100, (HEIGHT/2)+175, 200, 100}; //Location of "QUIT"
    SDL_RenderCopy(renderer, titleText, nullptr, &title); //Render "GAME PAUSED" to the screen
    SDL_RenderCopy(renderer, hostText, nullptr, &host); //Render "RESUME" to the screen
    SDL_RenderCopy(renderer, joinText, nullptr, &join);
    SDL_RenderCopy(renderer, quitText, nullptr, &quit); //Render "QUIT" to the screen

    switch(selection) { //Change where border is located based on which choice is selected
        case 1: { //HOST
            heightVal = (HEIGHT/2)-125;
            break;
        }
        case 2: { //JOIN
            heightVal = (HEIGHT/2)+30;
            break;
        }
        case 3: { //QUIT
            heightVal = (HEIGHT/2)+175;
        }
    }

    SDL_SetRenderDrawColor(renderer,212,175,55,0); //Gold color for border
    for(int i=0; i<5; i++) {
        border = {widthVal+i, heightVal+i, 300-2*i, 100-2*i};
        SDL_RenderDrawRect(renderer, &border); //Draw the golden rectangle
    }

    SDL_RenderPresent(renderer); //Draw everything to the screen
    SDL_DestroyTexture(titleText); //Destroy every texture to prevent memory leaks
    SDL_DestroyTexture(hostText);
    SDL_DestroyTexture(joinText);
    SDL_DestroyTexture(quitText);
}

void drawPause(SDL_Renderer* renderer, TTF_Font* font, bool selection) {
    SDL_SetRenderDrawColor(renderer,255,255,255,0); //Draw white background
    SDL_RenderClear(renderer);

    int menuWidth = (WIDTH/2), menuHeight = 2*(HEIGHT/3); //Bounds of the black box
    int menuX = (WIDTH - menuWidth)/2, menuY = (HEIGHT - menuHeight)/2; //Starting points of the black box
    int widthVal = (WIDTH/2)-145, heightVal = -1;
    SDL_Rect rect = {menuX, menuY, menuWidth, menuHeight}, border; //Black rectangle rect

    SDL_SetRenderDrawColor(renderer,0,0,0,0); //Choose black color
    SDL_RenderFillRect(renderer, &rect); //Fill in black rectangle

    SDL_Surface* surface = TTF_RenderText_Solid(font, "GAME PAUSED", {255,255,255,0}); //Game pause text
    SDL_Texture* pauseText = SDL_CreateTextureFromSurface(renderer, surface); //Make it a texture
    SDL_FreeSurface(surface); //Free the surface to prevent memory leaks
    surface = TTF_RenderText_Solid(font, "RESUME", {255,255,255,0}); //Resume text
    SDL_Texture* resumeText = SDL_CreateTextureFromSurface(renderer, surface); //Make it a texture
    SDL_FreeSurface(surface); //Free the surface to prevent memory leaks
    surface = TTF_RenderText_Solid(font, "QUIT", {255,255,255,0}); //Quit text
    SDL_Texture* quitText = SDL_CreateTextureFromSurface(renderer, surface); //Make it a texture
    SDL_FreeSurface(surface); //Free the surface to prevent memory leaks

    SDL_Rect pause = {(WIDTH/2)-200, (HEIGHT/2)-(menuHeight/2)+25, 400, 140}; //Location of "GAME PAUSED"
    SDL_Rect resume = {(WIDTH/2)-100, (HEIGHT/2)-50, 200, 100}; //Location of "RESUME"
    SDL_Rect quit = {(WIDTH/2)-100, (HEIGHT/2)+100, 200, 100}; //Location of "QUIT"
    SDL_RenderCopy(renderer, pauseText, nullptr, &pause); //Render "GAME PAUSED" to the screen
    SDL_RenderCopy(renderer, resumeText, nullptr, &resume); //Render "RESUME" to the screen
    SDL_RenderCopy(renderer, quitText, nullptr, &quit); //Render "QUIT" to the screen

    if(selection) { //Change where border is located based on which choice is selected
        heightVal = (HEIGHT/2)-50;
    } //Resume
    else {
        heightVal = (HEIGHT/2)+100;
    } //Quit

    SDL_SetRenderDrawColor(renderer,212,175,55,0); //Gold color for border
    for(int i=0; i<5; i++) {
        border = {widthVal+i, heightVal+i, 300-2*i, 100-2*i};
        SDL_RenderDrawRect(renderer, &border); //Draw the golden rectangle
    }

    SDL_RenderPresent(renderer); //Draw everything to the screen
    SDL_DestroyTexture(pauseText); //Destroy every texture to prevent memory leaks
    SDL_DestroyTexture(resumeText);
    SDL_DestroyTexture(quitText);
}

/********************************
*       Screen Functions        *
*********************************/
bool boolMenu(SDL_Renderer* renderer, TTF_Font* font, std::function<void(SDL_Renderer*,TTF_Font*,bool)>func) {
    //Generic two prompt selection menu that takes in a draw function as a parameter
    bool selection = true; //True == "resume" || False == "quit"
    func(renderer, font, selection);
    while(true) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) { //Typical event handler loop
            switch(event.type) {
                case SDL_MOUSEBUTTONDOWN: {
                    return selection;
                }
                case SDL_QUIT: {
                    return selection;
                }
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_ESCAPE: {
                            return true;
                        }
                        case SDLK_RETURN: {
                            return selection;
                        }
                        case SDLK_UP: { //User selects "RESUME"
                            selection = true; 
                            func(renderer, font, selection); //Only call the draw function whenever there is a change to be made to the screen   
                            break;
                        }
                        case SDLK_DOWN: { //User selects "QUIT"
                            selection = false; 
                            func(renderer, font, selection);    
                            break;
                        }
                    }
                    break;
                }
                case SDL_MOUSEMOTION: {
                    int xPos = event.motion.x;
                    int yPos = event.motion.y;
                    if(xPos > (WIDTH/2)-100 && xPos < (WIDTH/2)+100) {
                        if(yPos > (HEIGHT/2)-50 && yPos < (HEIGHT/2)+50) {
                            selection = true;
                        }
                        else if(yPos > (HEIGHT/2)+100 && yPos < (HEIGHT/2)+200) {
                            selection = false;
                        }
                        func(renderer, font, selection);
                    }
                    break;
                }
            }
        }
    }
    return selection;
}

template<typename starLL>
int triMenu(SDL_Renderer* renderer, TTF_Font* font, std::function<void(SDL_Renderer*,TTF_Font*,int)>func, starLL starList) {
    Uint64 frameStart = 0;
    int selection = 1, frameTime = 0;
    while(true) {
        frameStart = SDL_GetTicks64();
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_MOUSEBUTTONDOWN: {
                    return selection;
                }
                case SDL_QUIT: {
                    return selection;
                }
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_RETURN: {
                            return selection;
                        }
                        case SDLK_UP: {
                            if(selection == 1) {
                                selection = 3;
                            }
                            else {
                                selection -= 1;
                            }
                            break;
                        }
                        case SDLK_DOWN: {
                            if(selection == 3) {
                                selection = 1;
                            }
                            else {
                                selection += 1;
                            }
                            break;
                        }
                    }
                    break;
                }
                case SDL_MOUSEMOTION: {
                    int xPos = event.motion.x;
                    int yPos = event.motion.y;
                    if(xPos > (WIDTH/2)-100 && xPos < (WIDTH/2)+100) {
                        if(yPos > (HEIGHT/2)-125 && yPos < (HEIGHT/2)-25) {
                            selection = 1;
                        }
                        else if(yPos > (HEIGHT/2)+30 && yPos < (HEIGHT/2)+130) {
                            selection = 2;
                        }
                        else if(yPos > (HEIGHT/2)+175 && yPos < (HEIGHT/2)+275) {
                            selection = 3;
                        }
                    }
                    break;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer,0,0,0,0);
        SDL_RenderClear(renderer);
        starList.draw(renderer);
        func(renderer, font, selection);
        SDL_RenderPresent(renderer);
        frameTime = SDL_GetTicks64() - frameStart;
        if(frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    return selection;
}

#endif