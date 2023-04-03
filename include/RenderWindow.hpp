#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"

class RenderWindow{
    public:
        RenderWindow(const char *p_title,int p_width,int p_height);
        SDL_Texture *loadTexture(const char *p_path);
        void render(SDL_Texture *p_texture,int p_x,int p_y);
        void render(Entity &p_entity);
        void render(Entity &p_entity,float p_m);
        int  getRefreshRate();
        void cleanUp();
        void clear();
        void display();
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
};
