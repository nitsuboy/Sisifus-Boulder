#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char *p_title,int p_width,int p_height)
:window(NULL), renderer(NULL){
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,p_width,p_height,SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        std::cout << "WINDOW INIT FAIL" << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
}


SDL_Texture *RenderWindow::loadTexture(const char *path){
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, path);

    if (texture == NULL)
        std::cout << "LOAD TEXTURE FAIL" << SDL_GetError() << std::endl;
    
    return texture;
}

void RenderWindow::render(SDL_Texture *p_texture,int p_x,int p_y){
    SDL_Rect src;
    SDL_QueryTexture(p_texture,NULL,NULL,&src.w,&src.h);
    src.x = 0;
    src.y = 0;
    SDL_Rect dst;
    dst.x = p_x;
    dst.y = p_y;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(renderer,p_texture,&src,&dst);
}

void RenderWindow::render(Entity &p_entity){

    SDL_Rect src = p_entity.getFrame();
    SDL_Rect dst;
    dst.x = p_entity.getX();
    dst.y = p_entity.getY();
    dst.w = p_entity.getFrame().w;
    dst.h = p_entity.getFrame().h;

    SDL_RenderCopy(renderer,p_entity.getTex(),&src,&dst);
}

void RenderWindow::render(Entity &p_entity,float p_m){

    SDL_Rect src = p_entity.getFrame();
    SDL_Rect dst;
    dst.x = p_entity.getX();
    dst.y = p_entity.getY();
    dst.w = p_entity.getFrame().w * p_m;
    dst.h = p_entity.getFrame().h * p_m;

    SDL_RenderCopy(renderer,p_entity.getTex(),&src,&dst);
}

int RenderWindow::getRefreshRate(){

    int displayIndex = SDL_GetWindowDisplayIndex(window);
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(displayIndex, 0, &mode);
    return mode.refresh_rate;

}

void RenderWindow::cleanUp(){
    SDL_DestroyWindow(window);
}

void RenderWindow::clear(){
    SDL_RenderClear(renderer);
}

void RenderWindow::display(){
    SDL_RenderPresent(renderer);
}
