#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

bool run = 1;
int pressed = 0;
float v = 0;
int d = 0;
int s = 0;

/*u=n%10; 
t=(n/10)%10; 
h=(n/100)%10; 
th=n/1000; */

RenderWindow window("Sisifus Boulder",800,600);

SDL_Texture *numbers_tex[11] = {window.loadTexture("res/gfx/0.png"),window.loadTexture("res/gfx/1.png"),window.loadTexture("res/gfx/2.png"),window.loadTexture("res/gfx/3.png"),window.loadTexture("res/gfx/4.png"),
                                window.loadTexture("res/gfx/5.png"),window.loadTexture("res/gfx/6.png"),window.loadTexture("res/gfx/7.png"),window.loadTexture("res/gfx/8.png"),window.loadTexture("res/gfx/9.png"),
                                window.loadTexture("res/gfx/-.png")};
SDL_Texture *sisfo_tex = window.loadTexture("res/gfx/sisifus.png");
SDL_Texture *boulder_tex = window.loadTexture("res/gfx/boulder.png");
SDL_Texture *sky_tex = window.loadTexture("res/gfx/ceu.png");
SDL_Texture *montanha_tex0 = window.loadTexture("res/gfx/montanha.png");

Entity sky(0,0,sky_tex);
Entity sisifo(350,300,sisfo_tex);
Entity boulder(400,280,boulder_tex,32,16);
std::vector<Entity> montanha = {};

int sequence[4] = {SDL_SCANCODE_W,SDL_SCANCODE_D,SDL_SCANCODE_S,SDL_SCANCODE_A};

void input() {
    SDL_Event E;
    while (SDL_PollEvent(&E)){
        if (E.type == SDL_QUIT)
            run = false;
    }
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    if (keystates[sequence[pressed]] && !keystates[sequence[utils::next(pressed,4)]]){

        if (v > 1.5)
            v = 1.5;
        else
            v +=0.2;

        pressed = utils::next(pressed,4);
    }else{
        if (v < -0.5)
            v = -0.3;
        else
            v -=0.01;
    }
    std::cout << "velocidade : " << v << " distancia : " << s << std::endl;
}

void update(){
    window.render(sky);
    window.render(boulder,2);
    window.render(sisifo);
    boulder.animUpdate(v);
    for (Entity &e : montanha)
    {
        window.render(e);
        e.move(-0.86*v,0.5*v);
        if(e.getX() < -160){
            e.setX(160*5);
            e.setY(45);
        }
        if (e.getX() > 800)
        {
            e.setX(-160);
            e.setY(602);
        }
    }
    if (s < 0){
        window.render(numbers_tex[10],620,564);  
        window.render(numbers_tex[(s%10)*-1],764,564);
        window.render(numbers_tex[((s/10)%10)*-1],728,564);
        window.render(numbers_tex[((s/100)%10)*-1],692,564);
        window.render(numbers_tex[((s/1000)%10)*-1],656,564);
    }else{
        window.render(numbers_tex[s%10],764,564);
        window.render(numbers_tex[(s/10)%10],728,564);
        window.render(numbers_tex[(s/100)%10],692,564);
        window.render(numbers_tex[(s/1000)%10],656,564);
    }
    
    if (d >= 2000)
    {
        d = 0;
        s++;
    }
    if (d <= -2000)
    {
        d = 0;
        s--;
    }
    d += v*10;
}

int main(int argc, char *argv[])
{
    montanha.push_back(Entity(-80,(91*7)-45,montanha_tex0));
    for (int i = 0; i < 6; i++)
    {
        montanha.push_back(Entity(160*i,(92.5*(6-i))-45,montanha_tex0));
        montanha.push_back(Entity((160*i)+80,(92.5*(6-i))-91,montanha_tex0));
    }

    // error detection
    if (SDL_Init(SDL_INIT_VIDEO)> 0)
        std::cout << "SDL_INIT FAIL" << SDL_GetError() << std::endl;
    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_INIT FAIL" << SDL_GetError() << std::endl;
    
    // game loop
    const int TimeStepper = 60;

    while (run)
    {
        int startTicks = SDL_GetTicks();

        window.clear();
        input();
        update();
        window.display();
        
        int frameTicks = SDL_GetTicks() - startTicks;

        float fps = (frameTicks > 0) ? 1000.0f / frameTicks : 0.0f;
        
        std::cout << "fps = " << fps << std::endl;

        if(frameTicks < 1000 / TimeStepper)
            SDL_Delay(1000 / TimeStepper - frameTicks);

    }

    // quit
    window.cleanUp();
    SDL_Quit();

    return EXIT_SUCCESS;
}