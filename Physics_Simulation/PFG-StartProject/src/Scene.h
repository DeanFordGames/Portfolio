#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>
#include <random>

#include "GameObject.h"
#include "Camera.h"
#include "KinematicsObject.h"
#include "DynamicObject.h"

/*! \brief Brief description.
*  Scene class is a container for loading all the game objects in your simulation or your game. 
*  
*/

class Scene
{
public:

	/** Scene constructor
	* Currently the scene is set up in the constructor
	* This means the object(s) are loaded, given materials and positions as well as the camera and light
	*/
	Scene();
	/** Scene distructor
	*/
	~Scene();

	/** Scene update
	* This function is called for each simulation time step to
	* update on all objects in the scene
	*/
	void Update(float deltaTs, Input* input);

	/** 
	* Call this function to get a pointer to the camera
	* 
	*/
    Camera* GetCamera() { return _camera; }

	/** Draw the scene from the camera's point of view
	*
	*/
	void Draw();

private:

	/** A physics object
	*/
	std::vector<DynamicObject*> _physics_objects;

	std::vector<GameObject*> _scene_objects;
	 
	/** The main camera in the scene 
	*/
	Camera* _camera; 

	/**The position for a light that lits the scene
	*/
	glm::vec3 _lightPosition; 
	/** This matrix represents the camera's position and orientation 
	*/
	glm::mat4 _viewMatrix; 
	/** This matrix is the camera's lens
	*/
	glm::mat4 _projMatrix; 
	/** A boolen variable to control the start of the simulation This matrix is the camera's lens
	*/
	bool _simulation_start;

	glm::vec3 _v_i;//the intial velocity

};

#endif // !_SCENE_H_