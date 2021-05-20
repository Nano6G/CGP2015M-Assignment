#pragma once
//#include "Player.h"
#include "SDL.h"


class Bullet 
	//public Player
{
private:
	int bulletSpeed = 20;
	int bulletSpreadSpeed = 14;
	int changeX;
	int changeY;

	bool activeBullet = true;

	SDL_Rect bulletSprite;
	SDL_Rect spritePositionRect{ 0, 0, 16, 48 };
	double bulletAngle;

	SDL_Surface* bulletSur;
	SDL_Texture* bulletTex;
public:
	void Init(double playerAngle, int playerX, int playerY, SDL_Renderer* mainRenderer);
	void Update();
	void Render();

	SDL_Renderer* renderer;
};

