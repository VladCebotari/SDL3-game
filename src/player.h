#pragma once
#include <SDL3/SDL.h>



enum class PlayerState {
    Idle,
    Walking,
    Attacking,
    Guarding
};

typedef struct {
    int animationDelay;
    int frames;
    SDL_Texture* texture;
}animation;


typedef struct {
    animation idle;
    animation walk;
    animation attack;
    animation guard;
}animationType;


class Player
{
    private:
    SDL_Renderer* renderer;
    SDL_FRect src;
    SDL_FRect dest;
    animationType animations;
    animation* currentAnimation;
    int speed;
    int currentIndex;
    Uint64 lastUpdate;
    SDL_FlipMode flip;
    float sizeSprite;
    bool isWalking;
    PlayerState state;

    void showAnimation(const animation& animation);
    void initAnimation();
    public:
        void draw();
        void update ();
        void handleEvents(SDL_Event* event);
        void updateAnimation();

        Player(SDL_Renderer* renderer);
        ~Player();      
};
    
    

