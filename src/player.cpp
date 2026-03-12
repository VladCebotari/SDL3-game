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

    case PlayerState::Guarding:
        showAnimation(animations.guard);
        if(currentIndex == animations.guard.frames){
            state = PlayerState::Idle;
        }
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
     if (state != PlayerState::Attacking && state != PlayerState::Guarding) {
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
    switch (event->type)
    {
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            switch (event->button.button)
            {
                case SDL_BUTTON_LEFT:
                    state = PlayerState::Attacking;
                    break;

                case SDL_BUTTON_RIGHT:
                    state = PlayerState::Guarding;
                    break;

                default:
                    break;
            }
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            switch (event->button.button)
            {
                case SDL_BUTTON_RIGHT:
                    state = PlayerState::Idle;
                    break;
            }

    default:
        break;
    }
   
}


void Player::initAnimation(){
    animations.idle = {100,8,IMG_LoadTexture(renderer,"assets/Tiny Swords/Units/Red Units/Warrior/Warrior_Idle.png")};
    animations.walk = {100,6,IMG_LoadTexture(renderer,"assets/Tiny Swords/Units/Red Units/Warrior/Warrior_Run.png")};
    animations.attack = {80,4,IMG_LoadTexture(renderer,"assets/Tiny Swords/Units/Red Units/Warrior/Warrior_Attack1.png")};
    animations.guard = {100,6,IMG_LoadTexture(renderer,"assets/Tiny Swords/Units/Red Units/Warrior/Warrior_Guard.png")};
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