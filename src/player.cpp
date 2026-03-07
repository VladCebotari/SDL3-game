#include "player.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>

void Player::draw(){
    SDL_RenderTexture(renderer,texture,&src,&dest);
    
}
void Player::update (){
     const bool* keys = SDL_GetKeyboardState(NULL); 
    
    if(keys[SDL_SCANCODE_W]){
        dest.y -= speed;
    }
    if(keys[SDL_SCANCODE_S]){
        dest.y += speed;
    }
    if(keys[SDL_SCANCODE_D]){
        dest.x += speed;
    }
    if(keys[SDL_SCANCODE_A]){
        dest.x -= speed;
    }

    Uint64 timePassed = SDL_GetTicks();
    int delay = timePassed - lastUpdate;
    if(delay >= idle.animationDelay){ 
        lastUpdate = timePassed;

    currentIndex = (currentIndex+1) % idle.frames;
    src.x = currentIndex * sizeSprite;
        
    }
}

void Player:: handleEvents(){
  

}


Player::Player(SDL_Renderer* renderer,std::string texturePath) : renderer(renderer)
{
    idle.animationDelay = 100;
    idle.frames = 8;
    texture = IMG_LoadTexture(renderer,texturePath.c_str());
    sizeSprite = 192;
    dest = {509,259,sizeSprite ,sizeSprite};
    src = {0,0,sizeSprite ,sizeSprite };
    speed = 10;
        
}

Player::~Player()
{        
    SDL_DestroyTexture(texture);

}