#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<iostream>
#include"Engine.h"
#include<string>
#include<memory>

//screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main()
{
    

std::unique_ptr<Engine> engine= std::make_unique<Engine>();

engine->loadLevel();


return 0;
}