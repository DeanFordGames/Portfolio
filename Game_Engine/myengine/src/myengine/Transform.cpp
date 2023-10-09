#include "Transform.h"

namespace myengine
{

	Transform::Transform()
	{
		m_position = glm::vec3(0.0f, 0.0f, 0.0f);
		m_rotation = glm::vec3(0.0f, 1.0f, 0.0f);
		m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
		m_matrix = glm::mat4{ 1.0f };
		m_dirty = false;
		m_hasPhysics = false;
	}

	glm::mat4 Transform::getModelMatrix()
	{
		if (m_dirty == true)
		{//only updates the model matrix if a value has been changed
			m_matrix = glm::mat4{ 1.0f };
			m_matrix = glm::translate(m_matrix, m_position);
			m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
			m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			m_matrix = glm::scale(m_matrix, m_scale);
			m_dirty = false;
		}

		return m_matrix;
	}

}