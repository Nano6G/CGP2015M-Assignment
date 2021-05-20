// GameProgrammingAssessment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SDL.h"
#include "GameWorld.h"


int main(int argc, char *argv[])
{
    //Initialise all of SDL and SDL_Image
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(SDL_INIT_EVERYTHING);

    //Create GameWorld object
    GameWorld gameWorld1;

    //Initialise the object and display the splash screen for the gameworld
    gameWorld1.Init();
    gameWorld1.SplashScreen();

    //Exit the application after closing the libraries
    SDL_Quit();
    IMG_Quit();
    return 0;
    
}
