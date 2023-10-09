#pragma once

#include <SDL2/SDL.h>

namespace myengine
{
	struct Enviroment
	{
		Enviroment();

		float GetDeltaTime() { return deltaTime; }

		/**
		* tick set next deltaTime
		*/
		void tick();

	private:

		float deltaTime; ///< time since last frame
		float lastTime; ///< last frames time

	};
}