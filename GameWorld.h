#pragma once
#include "SDL.h"
#include "Timer.h"
#include "Player.h"

class GameWorld
{
private:
	const int DELTA_TIME = 60;
	bool running = false;
	bool fullscreen = false;
	Timer timer;
	Player player;
public:
	GameWorld();

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event _event;

	bool pressedKeys[256];

	//Initialisation function
	void Init();

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

