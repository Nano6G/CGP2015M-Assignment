#pragma once
#include <iostream>
#include "SDL.h"

//Based on class written by oszymanezyk@lincoln.ac.uk (part of game programming module)

class Timer
{
private:
	int startTicks;
public:
	Timer();

	void resetTicksTimer(); //Resets timer to 0
	int getTicks(); //Returns how much time has passed since timer has been reset
};

