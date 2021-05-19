#include "GameWorld.h"
#include <iostream>
#include "Player.h"

GameWorld::GameWorld()
{

}

void GameWorld::Init()
{
    //Create window
    window = SDL_CreateWindow("William Smith, 19693578, CGP2015 - GAME NAME", 200, 200, 1600, 900, SDL_WINDOW_SHOWN);

    //Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Sets window size to scale renderer from
    SDL_RenderSetLogicalSize(renderer, 1600, 900);

    //Initialises player object with current gameworld as parent
    player.parent = this;
    player.Init(50, 50, 60, 60);
}


void GameWorld::SplashScreen()
{
    while (displaySplash)
    {
        SDL_Surface* splashImage = IMG_Load("splash.png");
        SDL_Texture* splashTexture = SDL_CreateTextureFromSurface(renderer, splashImage);

        SDL_RenderCopy(renderer, splashTexture, NULL, NULL);

        //Present changes to window
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&_event))
        {

            if (_event.type == SDL_KEYDOWN && _event.key.repeat == NULL)
            {
                switch (_event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    displaySplash = false;
                    Run();
                    break;

                case SDLK_SPACE:
                    displaySplash = false;
                    Run();
                    break;
                }
            }
        }
    }
}


void GameWorld::Run()
{
    running = true;
    while (running)
    {
        Input();
        Update();
        Render(renderer);
    }
}

void GameWorld::ToggleFullscreen()
{
    if (fullscreen == false)
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        fullscreen = true;
    }
    else
    {
        SDL_SetWindowFullscreen(window, 0);
        fullscreen = false;
    }
}

void GameWorld::Input()
{
    timer.resetTicksTimer(); //resets frame timer to 0

    while (SDL_PollEvent(&_event))
    {
        if (_event.type == SDL_QUIT)
        {
            running = false;
        }

        if (_event.type == SDL_KEYDOWN && _event.key.repeat == NULL)
        {
            switch (_event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                running = false;
                break;
            case SDLK_w:
                pressedKeys[SDLK_w] = true;
                break;
            case SDLK_a:
                pressedKeys[SDLK_a] = true;
                break;
            case SDLK_s:
                pressedKeys[SDLK_s] = true;
                break;
            case SDLK_d:
                pressedKeys[SDLK_d] = true;
                break;
            case SDLK_r:
                pressedKeys[SDLK_r] = true;
                ToggleFullscreen();
            case SDLK_SPACE:
                pressedKeys[SDLK_SPACE] = true;
                break;
            }
        }

        if (_event.type == SDL_KEYUP && _event.key.repeat == NULL)
        {
            switch (_event.key.keysym.sym)
            {
            case SDLK_w:
                pressedKeys[SDLK_w] = false;
                break;
            case SDLK_a:
                pressedKeys[SDLK_a] = false;
                break;
            case SDLK_s:
                pressedKeys[SDLK_s] = false;
                break;
            case SDLK_d:
                pressedKeys[SDLK_d] = false;
                break;
            case SDLK_SPACE:
                pressedKeys[SDLK_SPACE] = false;
                break;
            }
        }
    }

    player.Input(pressedKeys);
}

void GameWorld::Update()
{
    player.Update();
}

void GameWorld::Render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);

    //Clears the window
    SDL_RenderClear(renderer);

    //Renders the player
    player.Render(renderer);

    //Present changes to window
    SDL_RenderPresent(renderer);

    
    if (timer.getTicks() < DELTA_TIME)
    {
        SDL_Delay(DELTA_TIME - timer.getTicks());
    }
    
}

void GameWorld::Quit()
{
    SDL_Quit();
    return;
}