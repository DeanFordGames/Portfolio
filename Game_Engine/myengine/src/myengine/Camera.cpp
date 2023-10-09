#include "Camera.h"

namespace myengine
{
	Camera::Camera() :
		m_viewMatrix(1.0f),
		m_cameraPosition(0.0f, 0.0f, 0.0f),
		m_cameraRotation(0.0f, 0.0f, 0.0f),
		m_cameraUp(0.0f, 1.0f, 0.0f),
		m_cameraRight(0.0f,0.0f,0.0f),
		m_cameraAngleX(0.0f),
		m_cameraAngleY(0.0f),
		m_mouseSpeed(0.005f)
	{
	}

	void Camera::tick()
	{//set up view matrix for this frame
		m_cameraRotation = glm::vec3(cos(m_cameraAngleY) * sin(m_cameraAngleX), sin(m_cameraAngleY), cos(m_cameraAngleY) * cos(m_cameraAngleX));
		m_cameraRight = glm::vec3(sin(m_cameraAngleX - 3.14f / 2.0f), 0, cos(m_cameraAngleX - 3.14f / 2.0f));
		m_cameraUp = glm::cross(m_cameraRight, m_cameraRotation);

		m_viewMatrix = glm::lookAt(m_cameraPosition, m_cameraPosition + m_cameraRotation, m_cameraUp);
	}

	void Camera::moveFoward(float _speed)
	{//move foward based on rotational value
		glm::vec3 translation = m_cameraRotation * _speed;
		m_cameraPosition += translation;
	}

	void Camera::moveBackward(float _speed)
	{//move backward based on rotational value
		glm::vec3 translation = m_cameraRotation * _speed;
		m_cameraPosition -= translation;
	}

	void Camera::moveLeft(float _speed)
	{//move to the left based on rotational value
		glm::vec3 translation = m_cameraRight * _speed;
		m_cameraPosition -= translation;
	}

	void Camera::moveRight(float _speed)
	{//move to the right based on rotational value
		glm::vec3 translation = m_cameraRight * _speed;
		m_cameraPosition += translation;
	}
}