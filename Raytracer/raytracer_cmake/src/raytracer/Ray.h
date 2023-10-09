#pragma once
#include <GLM/glm.hpp>

class Ray
{
public:

	Ray();

	glm::vec3 closestPointOnLine(glm::vec3 _queryPoint);

	glm::vec3 m_origin;
	glm::vec3 m_direction;

};