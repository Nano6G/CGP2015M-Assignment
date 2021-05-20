#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Bullet.h"
#include <list>
#include <vector>
#include "Enemy.h"

class GameWorld;

class Player
{
private:
	int changeX;
	int changeY;

	SDL_Rect playerSprite;
	SDL_Rect spritePositionRect{ 0, 0, 64, 64 };
	bool moving = false;
	bool firing = false;
	unsigned int changeTimeMS = 300;
	int firingDelay = 0;

	int dashCooldown = 0;

	double playerAngle = 0;

	int speed = 8;
	int dashSpeed = 50;

	SDL_Surface* playerSur;
	SDL_Texture* playerTex;

public:
	SDL_Renderer* renderer;

	void Init(int x, int y, int w, int h);
	void Input(bool pressedKeys[256], bool mouseClick);
	void Update();
	void Render();

	std::vector<Bullet*> bullets;

	GameWorld* parent;
};

