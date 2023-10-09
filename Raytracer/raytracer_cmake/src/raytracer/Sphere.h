#include <GLM/glm.hpp>

#include "Ray.h"
#include "Light.h"

class Sphere
{
public:

	Sphere();

	glm::vec3 calculateColour(Ray _ray, glm::vec3 _intersection, Light _light);

	glm::vec3 rayToSphere(Ray _ray);

	glm::vec3 m_surfaceColour;
	glm::vec3 m_centre;
	float m_radius;

	float m_shininess;
	float m_roughness;

	bool m_hit;

};
