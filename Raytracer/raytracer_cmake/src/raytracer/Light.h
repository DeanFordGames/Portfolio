#pragma once
#include <GLM/glm.hpp>

class Light
{
public:
	Light();

	glm::vec3 m_position;
	glm::vec3 m_lightColour;

private:
};