#include "GameWorld.h"
#include <iostream>
#include <ctime>
#include "Player.h"

void GameWorld::Init()
{
    SDL_Log("[OBJECT] Game world object initialised\n");

    //Create window
    window = SDL_CreateWindow("William Smith, 19693578, CGP2015 - GAME NAME", 200, 200, 1600, 900, SDL_WINDOW_SHOWN);

    //Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Sets window size to scale renderer from
    SDL_RenderSetLogicalSize(renderer, 1600, 900);

    //Initialises player object with current gameworld as parent
    player.renderer = renderer;
    player.parent = this;
    player.Init(0, 0, 64, 64);

    //Initialises enemy objects with current gameworld as parent
    enemy1.Init(500, 300, renderer);
    enemy2.Init(1400, 500, renderer);
}


void GameWorld::SplashScreen()
{
    while (displaySplash)
    {
        SDL_Surface* splashImage = IMG_Load("res/splash.png");
        SDL_Texture* splashTexture = SDL_CreateTextureFromSurface(renderer, splashImage);

        SDL_RenderCopy(renderer, splashTexture, NULL, NULL);

        //Present changes to window
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&_event))
        {
            if (_event.type == SDL_QUIT)
            {
                displaySplash = false;
            }

            if (_event.type == SDL_KEYDOWN && _event.key.repeat == NULL)
            {
                switch (_event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    SDL_Log("[SCREEN] Game starting...\n");
                    displaySplash = false;
                    Run();
                    break;

                case SDLK_SPACE:
                    SDL_Log("[SCREEN] Game starting...\n");
                    displaySplash = false;
                    Run();
                    break;

                case SDLK_r:
                    pressedKeys[SDLK_r] = true;
                    ToggleFullscreen();
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
        currentFrameCounter++;
    }
}

void GameWorld::ToggleFullscreen()
{
    SDL_Log("[SCREEN] Toggling Fullscreen\n");

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
        SDL_Keycode keyPressed = _event.key.keysym.sym;
        char timestr[32];
        //std::getTime(timestr, 32);

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
                SDL_Log("[KEY DOWN] time %d; code %d; char %s;", _event.key.timestamp, keyPressed, SDL_GetKeyName(keyPressed));
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
                SDL_Log("[KEY UP] time %d; code %d; char %s;", _event.key.timestamp, keyPressed, SDL_GetKeyName(keyPressed));
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

        if (_event.type == SDL_MOUSEBUTTONDOWN)
        {
            mouseClick = true;
        }
        if (_event.type == SDL_MOUSEBUTTONUP)
        {
            mouseClick = false;
        }
    }

    player.Input(pressedKeys, mouseClick);
}

void GameWorld::Update()
{
    player.Update();
}

void GameWorld::Render(SDL_Renderer* renderer)
{
    /*
    if (currentFrameCounter % 60 == 0)
    {
        SDL_Log("Current frame counter is divisible by 60\n");
    }
    */

    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);

    //Clears the window
    SDL_RenderClear(renderer);

    //Renders the player
    player.Render();

    //Renders the enemies
    enemy1.Render();
    enemy2.Render();


    //SDL_Surface* playerSur = IMG_Load("PlayerSprite.png");
    //SDL_Texture* playerTex = SDL_CreateTextureFromSurface(renderer, playerSur);
    //SDL_RenderCopy(renderer, playerTex, NULL, NULL);

    //Present changes to window
    SDL_RenderPresent(renderer);

    
    if (timer.getTicks() < DELTA_TIME)
    {
        SDL_Delay(DELTA_TIME - timer.getTicks());
    }


    //SDL_Log("Current frame ticks: %i", timer.getTicks());
    
}

void GameWorld::Quit()
{
    SDL_Quit();
    return;
}