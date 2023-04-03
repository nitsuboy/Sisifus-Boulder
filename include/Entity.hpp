#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>
#include "Utils.hpp"

class Entity {
    public:
        Entity(float p_x,float p_y, SDL_Texture *p_tex);
        Entity(float p_x,float p_y, SDL_Texture *p_tex,int p_sx,int p_f);
        void animUpdate();
        void animUpdate(float v);
        void move(float p_x, float p_y);
        float getX();
        float getY();
        void setX(float p_x);
        void setY(float p_y);
        SDL_Texture *getTex(); 
        SDL_Rect getFrame();
    private:
        bool animated = 0;
        int t;
        int f;
        int fa = 0;
        float x, y;
        SDL_Rect Frame;
        SDL_Texture *tex;
};