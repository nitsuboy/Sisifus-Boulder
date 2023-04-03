#include "Entity.hpp"
#include <iostream>

Entity::Entity(float p_x,float p_y,SDL_Texture *p_tex)
:x(p_x), y(p_y), tex(p_tex){
    SDL_QueryTexture(tex,NULL,NULL,&Frame.w,&Frame.h);
    Frame.x = 0;
    Frame.y = 0;
}

Entity::Entity(float p_x,float p_y,SDL_Texture *p_tex,int p_w,int p_f)
:x(p_x), y(p_y), tex(p_tex), animated(1), f(p_f){
    SDL_QueryTexture(tex,NULL,NULL,NULL,&Frame.h);
    Frame.w = p_w;
    Frame.x = 0;
    Frame.y = 0;
}

void Entity::animUpdate(){
    Frame.x = Frame.w * static_cast<int>((SDL_GetTicks() / 100) % f);
}

void Entity::animUpdate(float v){
    if(v > 0.1){
        if (t >= 30 - (int) v * 20){
            fa = utils::next(fa,f);
            Frame.x = fa * Frame.w;
            t=0;
        }else{
            t++;
        }
    }
}

void Entity::move(float p_x, float p_y){
    x += p_x;
    y += p_y;
};

float Entity::getX(){
    return x;
}

float Entity::getY(){
    return y;
}

void Entity::setX(float p_x){
    x = p_x;
}

void Entity::setY(float p_y){
    y = p_y;
}

SDL_Texture *Entity::getTex(){
    return tex;
}

SDL_Rect Entity::getFrame(){
    return Frame;
}