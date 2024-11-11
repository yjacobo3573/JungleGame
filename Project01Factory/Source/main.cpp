#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>

#include<iostream>

#include"Engine.h"

#include<string>

#include<memory>



int main()
{
    

std::unique_ptr<Engine> engine= std::make_unique<Engine>();

engine->loadLevel();


return 0;
}