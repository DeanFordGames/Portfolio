#pragma once

#include "btBulletDynamicsCommon.h"

#include <memory>
#include <rend/rend.h>

namespace myengine
{
	struct Physics
	{
		/*
		* Physics initializes the physics world
		*/
		Physics();

		void tick();

		/*
		* convertVectorTobt converts a vec3 to btVector 
		*/
		btVector3 convertVectorTobt(glm::vec3 _vec);
		/*
		* convertbtToVector converts a btVector to vec3
		*/
		glm::vec3 convertbtToVector(btVector3 _bt);

		std::shared_ptr<btDiscreteDynamicsWorld> m_world;///< holds the physics world
	private:
	};
}