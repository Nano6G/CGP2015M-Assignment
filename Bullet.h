#pragma once
#include "Player.h"
class Bullet :
	public Player
{
private:
	int speed = 20;
public:
	void Init();
	void Update();
	void Render();
};

