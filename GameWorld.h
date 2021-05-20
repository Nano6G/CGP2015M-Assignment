#pragma once
#include "SDL.h"
#include "Timer.h"
#include "Player.h"
#include "Enemy.h"

class GameWorld
{
private:
	const int DELTA_TIME = 20;
	bool displaySplash = true;
	bool running = false;
	bool fullscreen = false;

	Timer timer;
	Player player;
	Enemy enemy1;
	Enemy enemy2;

	int currentFrameCounter = 0;
	int gameTimer = 60;
	int ticksOnGameRun;
	bool mouseClick = false;

	unsigned int secondsPassed;

	SDL_AudioSpec audioSpec;
	Uint32 audioLength;
	Uint8 *audioBuffer;
	SDL_AudioDeviceID deviceID = SDL_OpenAudioDevice(NULL, 0, &audioSpec, NULL, 0);
	bool audioPlaying = true;

public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event _event;

	bool pressedKeys[256];

	//Initialisation function
	void Init();

	//Splash screen function
	void SplashScreen();

	//Funtion for starting and running the game loop
	void Run();

	//Game Loop Functions
	void Input();
	void Update();
	void Render(SDL_Renderer* renderer);

	void ToggleFullscreen();

	//Exit function
	void Quit();
};

