#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

class GameWorld;

class Enemy
{
private:
	int changeX;
	int changeY;
	SDL_Rect enemySprite;
	SDL_Rect spritePositionRect{ 0, 0, 64, 64 };

	double enemyAngle = 0;

	int speed = 10;

	SDL_Surface* enemySur;
	SDL_Texture* enemyTex;

public:
	SDL_Renderer* renderer;

	void Init(int x, int y, SDL_Renderer* mainRenderer);
	void Update();
	void Render();

	GameWorld* parent;
};



