#include "Component.h"

#include <rend/rend.h>
#include <memory>

#include "btBulletDynamicsCommon.h"

namespace myengine
{

	struct BoxCollider : Component
	{
		/**
		* BoxCollider sets initial size of collider
		*/
		BoxCollider();
		/**
		* initialize creates collider
		*/
		void initialize();

		std::shared_ptr<btCollisionShape> getCollider() { return m_collider; }

	//////////////////////////////////////////////////////////////////////////
		glm::vec3 getSize() { return m_size; }
		void setSize(glm::vec3 size) { m_size = size; }
		void changeSize(glm::vec3 size) { m_size += size; }

		glm::vec3 getOffset() { return m_offset; }
		void setOffset(glm::vec3 offset) { m_offset = offset; }
		void changeOffset(glm::vec3 offset) { m_offset += offset; }
	//////////////////////////////////////////////////////////////////////////

	private:
		glm::vec3 m_size; ///< scale of the box collider
		glm::vec3 m_offset; ///< offset for the 

		std::shared_ptr<btCollisionShape> m_collider;///< pointer to the bullet physics collider
	};

}