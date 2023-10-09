#include "BoxCollider.h"

#include "Entity.h"
#include "Transform.h"

namespace myengine
{
	BoxCollider::BoxCollider()
	{
		m_size = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	void BoxCollider::initialize()
	{
		m_collider = std::make_shared<btBoxShape>(getPhysics()->convertVectorTobt(m_size));
	}
}