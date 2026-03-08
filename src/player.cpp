#include "player.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>



void Player::draw(){
    if(isWalking) {
        SDL_RenderTextureRotated(renderer,animations.walk.texture,&src,&dest,0,NULL,flip);
    }else{
        SDL_RenderTextureRotated(renderer,animations.idle.texture,&src,&dest,0,NULL,flip);
    }   
    
}


void Player::showAnimation(const animation& newAnimation){

     if(currentAnimation != &newAnimation){
        currentAnimation = (animation*)&newAnimation;
        currentIndex = 0;
        lastUpdate = SDL_GetTicks();
    }


    Uint64 timePassed = SDL_GetTicks();
    int delay = timePassed - lastUpdate;
        if(delay >= newAnimation.animationDelay){ 
        lastUpdate = timePassed;

        currentIndex = (currentIndex+1) % newAnimation.frames;
        src.x = currentIndex * sizeSprite;
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
        flip = SDL_FLIP_NONE;
        
    }
    if(keys[SDL_SCANCODE_A]){
        dest.x -= speed;
        flip = SDL_FLIP_HORIZONTAL;
        isWalking = true;
    }
    
     if (isWalking) {
        showAnimation(animations.walk);
     }else{
        showAnimation(animations.idle); 
     }
    
}
void Player:: handleEvents(){
  

}

void Player::initAnimation(){
    animations.idle = {100,8,IMG_LoadTexture(renderer,"assets/Tiny Swords/Units/Red Units/Warrior/Warrior_Idle.png")};
    animations.walk = {100,6,IMG_LoadTexture(renderer,"assets/Tiny Swords/Units/Red Units/Warrior/Warrior_Run.png")};
    animations.attack = {100,4,IMG_LoadTexture(renderer,"assets/Tiny Swords/Units/Red Units/Warrior/Warrior_Attack1.png")};
    
}

Player::Player(SDL_Renderer* renderer,std::string texturePath) : renderer(renderer)
{
    initAnimation();
    
    lastUpdate = 0;
    sizeSprite = 192;
    dest = {509,259,sizeSprite ,sizeSprite};
    src = {0,0,sizeSprite ,sizeSprite };
    speed = 10;
    currentAnimation = nullptr;
}

Player::~Player()
{        
    SDL_DestroyTexture(animations.idle.texture);
    SDL_DestroyTexture(animations.walk.texture);
}