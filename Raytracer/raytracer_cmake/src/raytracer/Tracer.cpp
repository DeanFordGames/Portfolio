#include "Tracer.h"

#include <glm/gtc/random.hpp>

Tracer::Tracer()
{

}

glm::vec3 Tracer::returnColour(Ray _ray, Light _light, int _bounces)
{
	glm::vec3 rtn = glm::vec3(0.3f, 0.5f, 0.8f);
	float closestDis = 200.0f;
	glm::vec3 closestPoint = glm::vec3(0.0f);

	objectHit object = objectHit();
	object.m_ray = _ray;

	//check if there are objects in the scene
	if (m_objects.empty())
		return rtn;
	//checks if ray has run out of bounces
	if (_bounces <= 0)
		return glm::vec3(0.0f);

	glm::vec3 colour = glm::vec3(0.0f);

	//check each object to see if the ray hits them
	for (int i = 0; i < m_objects.size(); i++)
	{
		glm::vec3 pos = m_objects[i].rayToSphere(object.m_ray);
		if (m_objects[i].m_hit == true)
		{
			//checks distance from ray to intersection point
			//if its closer to the ray than the current closest point replace
			float dis = glm::distance(pos, object.m_ray.m_origin);
			if (dis < closestDis)
			{
				closestDis = dis;
				closestPoint = pos;
				object.m_hitIndex = i;
			}
		}
	}
	if (m_objects[object.m_hitIndex].m_hit == true)
	{
		//calculate colour
		colour = m_objects[object.m_hitIndex].calculateColour(object.m_ray, closestPoint, _light);

		//create a random vector for applying roughness
		glm::vec3 randOffset(glm::linearRand(-0.5f, 0.5f), glm::linearRand(-0.5f, 0.5f), glm::linearRand(-0.5f, 0.5f));
		glm::vec3 hitNormal = glm::normalize(closestPoint - m_objects[object.m_hitIndex].m_centre);
		//set new origin and direction for next bounce
		object.m_ray.m_origin = closestPoint + hitNormal * 0.0001f;
		object.m_ray.m_direction = glm::reflect(object.m_ray.m_direction, hitNormal + (randOffset * m_objects[object.m_hitIndex].m_roughness));

		//start next bounce calculation
		return colour + returnColour(object.m_ray, _light, _bounces - 1) * 0.5f;
	}
	else
	{
		colour += rtn;
	}

	rtn = colour;
	return rtn;
}
