#include "Timer.h"

Timer::Timer()
{
	startTicks = 0;
}

void Timer::resetTicksTimer()
{
	startTicks = SDL_GetTicks();
	//printf("Timer started %i \n", startTicks);
}

int Timer::getTicks()
{
	//printf("getTicks %i \n", SDL_GetTicks() - startTicks);
	return (SDL_GetTicks() - startTicks);
}
