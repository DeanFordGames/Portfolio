#include "Ray.h"

Ray::Ray()
{
	m_origin = glm::vec3(0.0f, 0.0f, 0.0f);
	m_direction = glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::vec3 Ray::closestPointOnLine(glm::vec3 _queryPoint)
{
	glm::vec3 temp = _queryPoint - m_origin;
	float dotP = glm::dot(temp, glm::normalize(m_direction));

	glm::vec3 rtn = m_origin + (glm::normalize(m_direction) * dotP);

	return rtn;
}