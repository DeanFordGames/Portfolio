#include "Keyboard.h"

#include <SDL2/SDL.h>

namespace myengine
{
	Keyboard::Keyboard()
	{
		for (int i = 0; i < 322; i++)
		{
			m_keys[i] = false;
			m_keyDown[i] = false;
			m_keyUp[i] = false;
		}
		m_mouseX = 0;
		m_mouseY = 0;
	}

	void Keyboard::setMouseMovement(float _x, float _y)
	{//if x or y is not zero i dont want it to try set another
		if(_x != 0)
			m_mouseX = _x;
		if(_y != 0)
			m_mouseY = _y;
	}
}