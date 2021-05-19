// GameProgrammingAssessment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SDL.h"
#include "GameWorld.h"


int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(SDL_INIT_EVERYTHING);

    GameWorld gameWorld1;

    gameWorld1.Init();
    gameWorld1.SplashScreen();


    SDL_Quit();
    IMG_Quit();
    return 0;
    
}
