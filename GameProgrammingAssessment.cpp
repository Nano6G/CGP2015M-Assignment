// GameProgrammingAssessment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SDL.h"
#include "GameWorld.h"

/*
#include "SZ_timer.h"
SZ_timer timer;
const int DELTA_TIME = 60;
bool running = true
*/


int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    GameWorld gameWorld1;

    gameWorld1.Init();
    gameWorld1.Run();

    printf("Exiting...");
    return 0;
    
}
