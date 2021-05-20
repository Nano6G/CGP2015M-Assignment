#include "GameWorld.h"
#include <iostream>
#include "Player.h"

void GameWorld::Init()
{
    //Log object initialisation
    SDL_Log("[OBJECT] Game world object initialised\n");

    //Create window
    window = SDL_CreateWindow("William Smith, 19693578, CGP2015 - Run n' Gun", 200, 200, 1600, 900, SDL_WINDOW_SHOWN);

    //Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Sets window size to scale renderer from
    SDL_RenderSetLogicalSize(renderer, 1600, 900);

    //Initialises player object with current gameworld as parent
    player.renderer = renderer;
    player.parent = this;
    player.Init(0, 0, 64, 64);

    //Initialises enemy objects with current gameworld as parent
    enemy1.Init(500, 300, renderer, 0);
    enemy2.Init(1400, 500, renderer, 1);

    //Loads background music file
    SDL_LoadWAV("res/Audio/impact-prelude.wav", &audioSpec, &audioBuffer, &audioLength);
    //Adds the audio to the queue and plays it
    SDL_QueueAudio(deviceID, audioBuffer, audioLength);
    SDL_PauseAudioDevice(deviceID, 0);
}


void GameWorld::SplashScreen()
{
    //Simple loop to display splash screen until user keypress
    while (displaySplash)
    {
        SDL_RenderClear(renderer);

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
    ticksOnGameRun = SDL_GetTicks();
    running = true;

    //Starts primary game loop
    while (running)
    {
        if (secondsPassed <= 60)
        {
            Input();
            Update();
            Render(renderer);
            currentFrameCounter++;
        }
        else
        {
            //Exits the game after 60 seconds have passed
            break;
        }
    }
}

void GameWorld::ToggleFullscreen() //Function to switch between display modes
{
    SDL_Log("[SCREEN] Toggling Fullscreen\n");

    if (fullscreen == false)
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP); //Sets to borderless fullscreen
        fullscreen = true;
    }
    else
    {
        SDL_SetWindowFullscreen(window, 0); //Sets to windowed
        fullscreen = false;
    }
}

void GameWorld::Input()
{
    timer.resetTicksTimer(); //resets frame timer to 0

    //Event input loop to store pressed keys in an array and perform gameworld level actions
    while (SDL_PollEvent(&_event))
    {
        SDL_Keycode keyPressed = _event.key.keysym.sym;

        if (_event.type == SDL_QUIT)
        {
            running = false;
        }

        if (_event.type == SDL_KEYDOWN && _event.key.repeat == NULL)
        {
            switch (_event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                running = false; //Exits the program
                break;
            case SDLK_w:
                pressedKeys[SDLK_w] = true;
                SDL_Log("[KEY DOWN] time %d; code %d; char %s;", _event.key.timestamp, keyPressed, SDL_GetKeyName(keyPressed)); //Logs key presses to console
                break;
            case SDLK_a:
                pressedKeys[SDLK_a] = true;
                SDL_Log("[KEY DOWN] time %d; code %d; char %s;", _event.key.timestamp, keyPressed, SDL_GetKeyName(keyPressed));
                break;
            case SDLK_s:
                pressedKeys[SDLK_s] = true;
                SDL_Log("[KEY DOWN] time %d; code %d; char %s;", _event.key.timestamp, keyPressed, SDL_GetKeyName(keyPressed));
                break;
            case SDLK_d:
                pressedKeys[SDLK_d] = true;
                SDL_Log("[KEY DOWN] time %d; code %d; char %s;", _event.key.timestamp, keyPressed, SDL_GetKeyName(keyPressed));
                break;
            case SDLK_r:
                pressedKeys[SDLK_r] = true;
                ToggleFullscreen();
            case SDLK_SPACE:
                pressedKeys[SDLK_SPACE] = true;
                SDL_Log("[KEY DOWN] time %d; code %d; char %s;", _event.key.timestamp, keyPressed, SDL_GetKeyName(keyPressed));
                break;
            case SDLK_m:
                pressedKeys[SDLK_m] = true;
                if (audioPlaying)
                {
                    SDL_Log("[AUDIO] Music stopped\n");
                    SDL_PauseAudioDevice(deviceID, 1);
                    audioPlaying = false;
                }
                else
                {
                    SDL_Log("[AUDIO] Music resumed\n");
                    SDL_PauseAudioDevice(deviceID, 0);
                    audioPlaying = true;
                }
                break;
            }
        }

        if (_event.type == SDL_KEYUP && _event.key.repeat == NULL)
        {
            switch (_event.key.keysym.sym)
            {
            case SDLK_w:
                pressedKeys[SDLK_w] = false;
                SDL_Log("[KEY UP] time %d; code %d; char %s;", _event.key.timestamp, keyPressed, SDL_GetKeyName(keyPressed)); //Logs key releases to the console
                break;
            case SDLK_a:
                pressedKeys[SDLK_a] = false;
                SDL_Log("[KEY UP] time %d; code %d; char %s;", _event.key.timestamp, keyPressed, SDL_GetKeyName(keyPressed));
                break;
            case SDLK_s:
                pressedKeys[SDLK_s] = false;
                SDL_Log("[KEY UP] time %d; code %d; char %s;", _event.key.timestamp, keyPressed, SDL_GetKeyName(keyPressed));
                break;
            case SDLK_d:
                pressedKeys[SDLK_d] = false;
                SDL_Log("[KEY UP] time %d; code %d; char %s;", _event.key.timestamp, keyPressed, SDL_GetKeyName(keyPressed));
                break;
            case SDLK_SPACE:
                pressedKeys[SDLK_SPACE] = false;
                SDL_Log("[KEY UP] time %d; code %d; char %s;", _event.key.timestamp, keyPressed, SDL_GetKeyName(keyPressed));
                break;
            }
        }

        //Determines mouse click state
        if (_event.type == SDL_MOUSEBUTTONDOWN)
        {
            mouseClick = true;
        }
        if (_event.type == SDL_MOUSEBUTTONUP)
        {
            mouseClick = false;
        }
    }

    //Calls the player input, passing the currently pressed keys and mouse click state
    player.Input(pressedKeys, mouseClick);
}

void GameWorld::Update()
{
    player.Update();
}

void GameWorld::Render(SDL_Renderer* renderer)
{
    //Timer implementation for deteremining time passed since the game begins
    unsigned int ticksSinceGameLaunch = SDL_GetTicks() - ticksOnGameRun;
    secondsPassed = (ticksSinceGameLaunch / 1000);

    //Rudimentary delay of logging the time passed since game launch (prevents the time passed logging every frame)
    if (currentFrameCounter % 40 == 0)
    {
        SDL_Log("[TIMER] Seconds passed since game launch: %i", secondsPassed);
    }

    //Basic gray background
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);

    //Clears the window
    SDL_RenderClear(renderer);

    //Renders the player
    player.Render();

    //Renders the enemies
    enemy1.Render();
    enemy2.Render();


    //Present changes to window
    SDL_RenderPresent(renderer);

    
    if (timer.getTicks() < DELTA_TIME)
    {
        SDL_Delay(DELTA_TIME - timer.getTicks());
    }
    
}

void GameWorld::Quit() //Function to exit the game
{
    SDL_Quit();
    return;
}