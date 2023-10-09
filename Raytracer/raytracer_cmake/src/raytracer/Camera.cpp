#include "Camera.h"
#include <glm/gtc/random.hpp>

Camera::Camera()
{
	//initalize camera matricies
	m_projMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	m_viewMatrix = glm::mat4(1);
}

Ray Camera::returnRay(glm::ivec2 _pos, glm::ivec2 _screen)
{
	Ray rtn = Ray();

	float x = static_cast <float>(_pos.x);
	float sX = static_cast <float> (_screen.x);

	float y = static_cast <float>(_pos.y);
	float sY = static_cast <float> (_screen.y);

	//create random position around pixel for multiple samples
	x += glm::linearRand(-0.5f, 0.5f);
	y += glm::linearRand(-0.5f, 0.5f);

	//change screen space to ndc space
	float ndcX = (x / sX - 0.5f) * 2.0f;
	float ndcY = (y / sY - 0.5f) * 2.0f;

	glm::vec4 origin = glm::vec4(ndcX, ndcY, -1.0f, 1.0f);
	glm::vec4 dir = glm::vec4(ndcX, ndcY, 1.0f, 1.0f);

	//initalize ray position and dirrection
	origin = glm::inverse(m_projMatrix) * origin;
	dir = glm::inverse(m_projMatrix) * dir;
	
	origin /= origin.w;
	dir /= dir.w;

	origin = glm::inverse(m_viewMatrix) * origin;
	dir = glm::inverse(m_viewMatrix) * dir;

	rtn.m_origin = origin;
	rtn.m_direction = glm::normalize(dir - origin);

	return rtn;
}