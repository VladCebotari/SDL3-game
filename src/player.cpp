#include "player.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>



void Player::draw(){
    SDL_RenderTextureRotated(renderer,currentAnimation->texture,&src,&dest,0,NULL,flip);

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

        currentIndex = currentIndex % newAnimation.frames;
        src.x = currentIndex * sizeSprite;
        currentIndex++;
    }
}


void Player::updateAnimation(){
    switch (state)
    {
    case PlayerState::Idle:
        showAnimation(animations.idle);
        break;
    case PlayerState::Walking:
        showAnimation(animations.walk);
        break;
    case PlayerState::Attacking:
        showAnimation(animations.attack);
        if(currentIndex == animations.attack.frames){
            state = PlayerState::Idle;
        }
        break;
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
     if (state != PlayerState::Attacking) {
        if(isWalking){
            state = PlayerState::Walking;
        }
        else{
            state = PlayerState::Idle;
        }  
    }
    updateAnimation();
    
}

void Player:: handleEvents(SDL_Event* event){
    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN ) {
        state = PlayerState::Attacking;
        }
}




void Player::initAnimation(){
    animations.idle = {100,8,IMG_LoadTexture(renderer,"assets/Tiny Swords/Units/Red Units/Warrior/Warrior_Idle.png")};
    animations.walk = {100,6,IMG_LoadTexture(renderer,"assets/Tiny Swords/Units/Red Units/Warrior/Warrior_Run.png")};
    animations.attack = {120,4,IMG_LoadTexture(renderer,"assets/Tiny Swords/Units/Red Units/Warrior/Warrior_Attack1.png")};
    
}

Player::Player(SDL_Renderer* renderer) : renderer(renderer)
{
    initAnimation();
    lastUpdate = 0;
    sizeSprite = 192;
    dest = {509,259,sizeSprite ,sizeSprite};
    src = {0,0,sizeSprite ,sizeSprite };
    speed = 10;
    currentAnimation = nullptr;
    state = PlayerState::Idle;
    currentIndex = 0;
    isWalking = false;
    flip = SDL_FLIP_NONE;
}

Player::~Player()
{        
    SDL_DestroyTexture(animations.idle.texture);
    SDL_DestroyTexture(animations.walk.texture);
    SDL_DestroyTexture(animations.attack.texture);
}