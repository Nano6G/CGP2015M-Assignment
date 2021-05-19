#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

class GameWorld;

class Player
{
private:
	SDL_Renderer* renderer;
	int changeX;
	int changeY;
	SDL_Rect playerSprite;
	int dashCooldown = 0;

	SDL_Surface* playerSur = IMG_Load("PlayerSprite.png");
	SDL_Texture* playerTex = SDL_CreateTextureFromSurface(renderer, playerSur);

public:
	Player();

	//int playerX;
	//int playerY;
	//int playerW;
	//int playerH;

	void Init(int x, int y, int w, int h);
	void Input(bool pressedKeys[256]);
	void Update();
	void Render(SDL_Renderer* renderer);

	GameWorld* parent;
};

