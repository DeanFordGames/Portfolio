#pragma once

#include <rend/rend.h>

namespace myengine
{

	struct Camera
	{
		/**
		* camera initializes all values
		*/
		Camera();

		glm::mat4 getViewMatrix() { return m_viewMatrix; }

		void tick();
		
		void setPosition(glm::vec3 _pos) { m_cameraPosition = _pos; }
		void changePosition(glm::vec3 _pos) { m_cameraPosition += _pos; }

		void changeCameraAngle(float _x, float _y) { m_cameraAngleX -= _x * m_mouseSpeed; m_cameraAngleY -= _y * m_mouseSpeed; }
		void setCameraAngle(float _x, float _y) { m_cameraAngleX = _x; m_cameraAngleY = _y; }
		
		float getCameraAngleX() { return m_cameraAngleX; }
		float getCameraAngleY() { return m_cameraAngleY; }
		
		void setMouseSpeed(float _speed) { m_mouseSpeed = _speed; }

		/**
		* moveFoward moves the camera foward based on its rotation
		*/
		void moveFoward(float _speed);
		/**
		* moveBackward moves the camera backward based on its rotation
		*/
		void moveBackward(float _speed);
		/**
		* moveleft moves the camera to the left based on its rotation
		*/
		void moveLeft(float _speed);
		/**
		* moveFoward moves the camera to the right based on its rotation
		*/
		void moveRight(float _speed);

	private:
		glm::mat4 m_viewMatrix;///< view matrix for the camera

		glm::vec3 m_cameraPosition; ///< holds x, y, z position for camera
		glm::vec3 m_cameraRotation; ///< holds x, y, z rotational values
		glm::vec3 m_cameraUp; ///< up value
		glm::vec3 m_cameraRight; ///< holds a position for right side of camera

		float m_cameraAngleX; ///< rotational x axis
		float m_cameraAngleY; ///< rotational y axis

		float m_mouseSpeed; ///< speed to mouse movement
	};

}