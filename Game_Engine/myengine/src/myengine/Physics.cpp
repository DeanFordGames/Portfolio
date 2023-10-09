#include "Physics.h"

namespace myengine
{
	Physics::Physics()
	{
		//collision configuration contains default setup for memory, collision setup
		btDefaultCollisionConfiguration* collisionConfig = new btDefaultCollisionConfiguration();

		//use the default collision dispatcher
		btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfig);

		//btDbvtBroadphase is a good general purpose broadphase
		btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

		//the default constraint solver
		btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

		m_world = std::make_shared<btDiscreteDynamicsWorld>(dispatcher, overlappingPairCache, solver, collisionConfig);

		m_world->setGravity(btVector3(0.0f, -9.8f, 0.0f));
	}

	void Physics::tick()
	{//calculate all physics for world
		m_world->stepSimulation(1.0f / 60.0f, 10);
	}

	btVector3 Physics::convertVectorTobt(glm::vec3 _vec)
	{
		btVector3 rtn;

		rtn.setX(_vec.x);
		rtn.setY(_vec.y);
		rtn.setZ(_vec.z);

		return rtn;
	}

	glm::vec3 Physics::convertbtToVector(btVector3 _bt)
	{
		glm::vec3 rtn;

		rtn.x = _bt.getX();
		rtn.y = _bt.getY();
		rtn.z = _bt.getZ();

		return rtn;
	}
}