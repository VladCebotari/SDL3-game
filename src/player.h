#pragma once
#include <SDL3/SDL.h>
#include <string>


typedef struct {
    int animationDelay;
    int frames;
    SDL_Texture* texture;
}animation;


typedef struct {
    animation idle;
    animation walk;
    animation attack;
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
    float sizeSprite;
    bool isWalking;
    SDL_FlipMode flip;



    void showAnimation(const animation& animation);
    void initAnimation();
    public:
        void draw();
        void update ();
        void handleEvents();
        

        Player(SDL_Renderer* renderer,std::string texturePath);
        ~Player();      
};
    
    

