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
}animationType;


class Player
{
    private:
    SDL_Renderer* renderer;
    SDL_FRect src;
    SDL_FRect dest;
    animationType animations;
    int speed;
    int currentIndex;
    int lastUpdate;
    float sizeSprite;
    bool isWalking;

    public:
        void draw();
        void update ();
        void handleEvents();
        

        Player(SDL_Renderer* renderer,std::string texturePath);
        ~Player();
        
};
    
    
