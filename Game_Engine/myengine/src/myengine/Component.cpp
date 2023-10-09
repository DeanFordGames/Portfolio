#include "Component.h"

namespace myengine
{

	void Component::onTick() {}
	void Component::onDisplay() {}

	void Component::tick()
	{
		onTick();
	}

	void Component::display()
	{
		onDisplay();
	}
}