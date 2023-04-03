#pragma once

#include <SDL2/SDL.h>

namespace utils{
    
    inline float hireTimeInSeconds(){
        float t = SDL_GetTicks();
        t *= 0.001f;
        return t;
    }

    inline int next(int i,int p_m){
        if (i == p_m - 1)
            return 0;
        else
            return i + 1;
    }
}