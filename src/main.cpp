#define SDL_MAIN_USE_CALLBACKS 1
#include "player.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>



static SDL_Window* window;
static SDL_Renderer* renderer;
Player *player {};

SDL_AppResult SDL_AppInit(void **appstate,int argc,char *argv[])
{

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer("First App",1200,800,0,&window,&renderer);

    player = new Player(renderer,"assets/Tiny Swords /Units/Red Units/Warrior/Warrior_Idle.png");
    

    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppEvent(void *appstate,SDL_Event* event){
    switch (event->type){
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;    

        default:
            break;
    }
    player->handleEvents();
    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(void* appstate){
    SDL_SetRenderDrawColor(renderer,210,210,210,255);
    SDL_RenderClear(renderer);

    player->update();
    player->draw();
    

    
    SDL_RenderPresent(renderer);
    SDL_Delay(16);
    return SDL_APP_CONTINUE;
} 

void SDL_AppQuit(void *appstate,SDL_AppResult result){

}
