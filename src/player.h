#pragma once
#include <SDL3/SDL.h>
#include <string>
//struct animationType
//tipul de animatie(run,attack etc) c.string la texture path 


typedef struct {
    int animationDelay;
    int frames;
}animation;


typedef struct {
    animation data;
    const char* file;
}animationType;


class Player
{
    private:
    SDL_Renderer* renderer;
    SDL_FRect src;
    SDL_FRect dest;
    SDL_Texture* texture;
    animation idle;
    int speed;
    int currentIndex;
    int lastUpdate;
    float sizeSprite;
    

    public:
        void draw();
        void update ();
        void handleEvents();
        

        Player(SDL_Renderer* renderer,std::string texturePath);
        ~Player();
        
};
    
    
