#include "Sphere.h"

#include <iostream>

Sphere::Sphere()
{
	m_centre = glm::vec3(0.0f, 0.0f, -10.0f);
	m_surfaceColour = glm::vec3(1.0f, 0.3f, 0.3f);
	m_radius = 1.0f;
	m_hit = false;
	m_shininess = 64.0f;
	m_roughness = 0.0f;
}

glm::vec3 Sphere::calculateColour(Ray _ray, glm::vec3 _intersection, Light _light)
{
	glm::vec3 sphereNormal = glm::normalize(_intersection - m_centre);
	glm::vec3 lightColour = _light.m_lightColour;

	//directional vector pointing towards light
	glm::vec3 surfaceToLight = glm::normalize(_light.m_position - _intersection);
	//directional vector pointing towards eye
	glm::vec3 surfaceToEye = glm::normalize(_ray.m_origin - _intersection);


	//calculate diffuse colour
	glm::vec3 diffuse = m_surfaceColour * lightColour * glm::max(glm::dot(sphereNormal, surfaceToLight), 0.0f);

	//stop specular light from appearing on oppisite side of sphere
	glm::vec3 facing = glm::vec3(0.0f);
	if (glm::dot(sphereNormal, surfaceToLight) > 0)
		facing = glm::vec3(1.0f);

	//halfway point between ray and light
	glm::vec3 halfway = glm::normalize(surfaceToEye + surfaceToLight);
	//calculate specular colour 
	glm::vec3 specular = m_surfaceColour * lightColour * facing * powf(glm::max(glm::dot(sphereNormal, halfway), 0.0f), m_shininess);

	//return value of colour
	glm::vec3 rtn = diffuse + specular;

	m_hit = false;

	return rtn;
}

glm::vec3 Sphere::rayToSphere(Ray _ray)
{
	// checking if ray's origin is inside sphere
	if( glm::distance(_ray.m_origin, m_centre) > m_radius )
	{

		glm::vec3 temp = m_centre - _ray.m_origin;
		// distance from ray's origin to closest point to centre of sphere
		float rayLengthToClosestPoint = glm::dot(temp, _ray.m_direction);

		// closest point on line
		glm::vec3 point = _ray.m_origin + (_ray.m_direction * rayLengthToClosestPoint);

		// Distance 'd' in the equations
		float distToClosestPoint = glm::distance(point, m_centre);


		//if (glm::dot(glm::normalize(ray._direction), (point - ray._origin)) <= 0.0f)

		// main intersection check
		if(distToClosestPoint <= m_radius )
		{
			float x = glm::sqrt(m_radius * m_radius - distToClosestPoint * distToClosestPoint);
			//check if sphere is behind ray origin
			if (rayLengthToClosestPoint - x > 0.0f)
			{

				m_hit = true;
				//intersection point
				return _ray.m_origin + (glm::dot((m_centre - _ray.m_origin), _ray.m_direction) - x) * _ray.m_direction;
			}
			else
			{
				m_hit = false;
				return glm::vec3(0.0f, 0.0f, 0.0f);
			}

		}
		else
		{
			m_hit = false;
			return glm::vec3(0.0f, 0.0f, 0.0f);
		}
	}
	else
	{
		m_hit = false;
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
}