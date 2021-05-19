#pragma once
#include <iostream>
#include "SDL.h"

class GameWorld;

class Player
{
private:
	SDL_Renderer* renderer;

	SDL_Rect playerSprite;
public:
	Player();

	//int playerX;
	//int playerY;
	//int playerW;
	//int playerH;

	void Init(int x, int y, int w, int h);
	void Input();
	void Update(int changeX, int changeY);
	void Render(SDL_Renderer* renderer);

	GameWorld* parent;
};

