#include "Light.h"

Light::Light()
{
	m_position = glm::vec3(10.0f, -10.0f, -1.0f);
	m_lightColour = glm::vec3(1.0f, 1.0f, 1.0f);
}