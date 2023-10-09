#include "Enemy.h"


void Enemy::onTick()
{
	std::shared_ptr<Transform> t = getEntity()->getComponent<Transform>();

	t->changePosition(glm::vec3(0.0f, 0.0f, -7.0f) * getEnviroment()->GetDeltaTime());

	glm::vec3 pos = t->getPosition();

	if (pos.z < -2.0f)
	{
		getEntity()->kill();
	}
}