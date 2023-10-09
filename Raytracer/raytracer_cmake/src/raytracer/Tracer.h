#include "Ray.h"
#include "Sphere.h"
#include "Light.h"
#include "ObjectHit.h"


#include <GLM/glm.hpp>
#include <vector>

class Tracer
{
public:
	Tracer();

	glm::vec3 returnColour(Ray _ray, Light _light, int _bounces);
	void addSphere() { m_objects.push_back(Sphere()); }

	std::vector<Sphere> m_objects;
};