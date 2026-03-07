#include "player.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>



void Player::draw(){
    if(Player::isWalking) {
        SDL_RenderTexture(renderer,animations.walk.texture,&src,&dest);
    }else{
        SDL_RenderTexture(renderer,animations.idle.texture,&src,&dest);
    }

    
}
void Player::update (){
     const bool* keys = SDL_GetKeyboardState(NULL); 
     isWalking = false;
    if(keys[SDL_SCANCODE_W]){
        dest.y -= speed;
        isWalking = true;
    }
    if(keys[SDL_SCANCODE_S]){
        dest.y += speed;
        isWalking = true;
    }
    if(keys[SDL_SCANCODE_D]){
        dest.x += speed;
        isWalking = true;
    }
    if(keys[SDL_SCANCODE_A]){
        dest.x -= speed;
        isWalking = true;
    }

    Uint64 timePassed = SDL_GetTicks();
    int delay = timePassed - lastUpdate;

    if (isWalking) {
        if(delay >= animations.walk.animationDelay){ 
        lastUpdate = timePassed;

        currentIndex = (currentIndex+1) % animations.walk.frames;
        src.x = currentIndex * sizeSprite;
        }
    }else {
        if(delay >= animations.idle.animationDelay){ 
        lastUpdate = timePassed;

        currentIndex = (currentIndex+1) % animations.idle.frames;
        src.x = currentIndex * sizeSprite;     
            }
        }
    

}
void Player:: handleEvents(){
  

}


Player::Player(SDL_Renderer* renderer,std::string texturePath) : renderer(renderer)
{
    animations.idle = {100,8,IMG_LoadTexture(renderer,texturePath.c_str())};
    animations.walk = {100,6,IMG_LoadTexture(renderer,"assets/Tiny Swords/Units/Red Units/Warrior/Warrior_Run.png")};
    currentIndex = 0;
    lastUpdate = 0;
    sizeSprite = 192;
    dest = {509,259,sizeSprite ,sizeSprite};
    src = {0,0,sizeSprite ,sizeSprite };
    speed = 10;
        
}

Player::~Player()
{        
    SDL_DestroyTexture(animations.idle.texture);
    SDL_DestroyTexture(animations.walk.texture);

}