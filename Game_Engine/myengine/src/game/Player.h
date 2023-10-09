#include <myengine/myengine.h>

using namespace myengine;

struct Player : Component
{
	Player();


private:
	void onTick();

	bool m_freezeAxis;
};