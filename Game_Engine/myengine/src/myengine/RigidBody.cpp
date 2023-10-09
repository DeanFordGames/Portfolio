#include "RigidBody.h"

#include "BoxCollider.h"
#include "Core.h"
#include "Transform.h"

#include <list>
#include <memory>

namespace myengine
{
	RigidBody::RigidBody()
	{
		m_transform.setIdentity();
		m_mass = 1.0f;
	}

	void RigidBody::initialize()
	{
		//setting up rigidbody transform
		m_transform.setOrigin(getPhysics()->convertVectorTobt(getEntity()->getComponent<Transform>()->getPosition()));
		btVector3 localInertia(0, 0, 0);

		//if rigidbody has mass calculate inertia
		if(m_mass != 0.0f)
			getEntity()->getComponent<BoxCollider>()->getCollider()->calculateLocalInertia(m_mass, localInertia);

		//setting up rigidbody info then creating rigidbody
		btDefaultMotionState* motionState = new btDefaultMotionState(m_transform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(m_mass, motionState, getEntity()->getComponent<BoxCollider>()->getCollider().get(), localInertia);
		m_body = std::make_shared<btRigidBody>(rbInfo);

		//add rigidbody to physics world
		getPhysics()->m_world->addRigidBody(m_body.get());

		//set physics true in transform
		getEntity()->getComponent<Transform>()->setHasPhysics(true);
	}

	void RigidBody::onTick()
	{//updates the position in transform for rendering
		m_body->getMotionState()->getWorldTransform(m_transform);
		getEntity()->getComponent<Transform>()->setPosition(getPhysics()->convertbtToVector(m_transform.getOrigin()));
	}

	void RigidBody::addImpulse(glm::vec3 _impulse)
	{
		m_body->activate();
		m_body->applyImpulse(getPhysics()->convertVectorTobt(_impulse), btVector3(0.0f, 0.0f, 0.0f));
	}

	void RigidBody::addForce(glm::vec3 _force)
	{
		m_body->activate();
		m_body->applyForce(getPhysics()->convertVectorTobt(_force), btVector3(0.0f, 0.0f, 0.0f));
	}

}