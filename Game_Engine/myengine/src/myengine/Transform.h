#include "Component.h"

#include "RigidBody.h"
#include <rend/rend.h>

namespace myengine
{
	/**
	* Component provideing the positional values for the entity 
	*/
	struct Transform : Component
	{
		/**
		* Transform initalizes all the vectors and matrices
		*/
		Transform();

		void changePosition(glm::vec3 _pos) 
		{ 
			if (m_hasPhysics) { m_rb->addImpulse(_pos); }
			else { m_position += _pos; m_dirty = true; }
		}
		glm::vec3 getPosition() { return m_position; }
		void setPosition(glm::vec3 _pos) { m_position = _pos; m_dirty = true; }

		void changeRotation(glm::vec3 _rot) { m_rotation += _rot; m_dirty = true; }
		glm::vec3 getRotation() { return m_rotation; }
		void setRotaion(glm::vec3 _rot) { m_rotation = _rot; m_dirty = true; }

		glm::vec3 getScale() { return m_scale; }
		void setScale(glm::vec3 _s) { m_scale = _s; m_dirty = true; }
		void changeScale(glm::vec3 _s) { m_scale += _s; m_dirty = true; }

		/**
		* sets the rigidbody and has physics
		* \param true if has rigidbody
		*/
		void setHasPhysics(bool _physics) { m_hasPhysics = _physics; m_rb = getEntity()->getComponent<RigidBody>(); }

		/**
		* creates the required model matrix for the entity
		* \return created model matrix
		*/
		glm::mat4 getModelMatrix();


	private:
		glm::vec3 m_position; ///< x, y, z position of entity
		glm::vec3 m_rotation; ///< rotation of entity in euler angles
		glm::vec3 m_scale; ///< scale of entity

		glm::mat4 m_matrix; ///< model matrix for transform

		bool m_dirty; ///< check if any matrix value needs to change
		bool m_hasPhysics; ///< check if entity has physics

		std::shared_ptr<RigidBody> m_rb; ///< current entities rigidbody
	};
}