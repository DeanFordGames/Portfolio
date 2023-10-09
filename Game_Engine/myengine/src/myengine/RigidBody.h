#pragma once

#include "Component.h"

#include "Keyboard.h"
#include "btBulletDynamicsCommon.h"

namespace myengine
{
	/**
	* Component provides the physics for the Entity 
	*/
	struct RigidBody : Component
	{

		RigidBody();

		/**
		* initialize is called after creation to initialize rigidbody
		*/
		void initialize();

		void setMass(float _mass) { m_mass = _mass; }

		/**
		* addImpulse adds impulse physics to rigidbody
		* \param amount being pushed by
		*/
		void addImpulse(glm::vec3 _impulse);
		/**
		* addForce adds force physics to rigidbody
		* \param amount being pushed by
		*/
		void addForce(glm::vec3 _force);

		/**
		* freezePositionAxis is to freeze a perticular movement axis from being used with the rigidbody
		*/
		void freezePositionAxis(glm::vec3 _axis) { m_body->setLinearFactor(btVector3(_axis.x, _axis.y, _axis.z)); }
		/**
		* freezeAngularAxis is to freeze a perticular rotational axis from being used with the rigidbody
		*/
		void freezeAngularAxis(glm::vec3 _axis) { m_body->setAngularFactor(btVector3(_axis.x, _axis.y, _axis.z)); }

		/**
		* onTick Update function 
		*/
		void onTick();

	private:
		btTransform m_transform; ///< transform of rigidbody
		btScalar m_mass;///< mass of rigidbody
		std::shared_ptr<btRigidBody> m_body;///< rigidbody used for physics
	};

}