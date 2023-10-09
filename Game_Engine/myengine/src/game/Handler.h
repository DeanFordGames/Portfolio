#include <myengine/myengine.h>

#include "Enemy.h"

using namespace myengine;

struct Handler : Component
{
	Handler();

private:
	void onTick();

	float m_spawnTime;
};