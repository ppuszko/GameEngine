#pragma once
#include <SDL.h>

class DeltaTime
{
public:

	void initLastTime()
	{
		lastTime = SDL_GetTicks();
	}

	float getDeltaTime()
	{
		Uint32 currentTime = SDL_GetTicks();
		float deltaTime = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;
		return deltaTime;
	}

private:
	Uint32 lastTime;
};