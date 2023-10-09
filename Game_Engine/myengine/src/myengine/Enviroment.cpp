#include "Enviroment.h"

namespace myengine
{
	Enviroment::Enviroment()
	{
		deltaTime = 0.0f;
		lastTime = SDL_GetTicks();;
	}

	void Enviroment::tick()
	{
		float time = SDL_GetTicks();
		float diff = time - lastTime;
		deltaTime = diff / 1000.0f;
		lastTime = time;
	}
}