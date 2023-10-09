#include "Scene.h"

/*! \brief Brief description.
*  Scene class is a container for loading all the game objects in your simulation or your game.
*
*/
Scene::Scene()
{
	// Set up your scene here......
	// Set a camera
	_camera = new Camera();
	// Don't start simulation yet
	_simulation_start = false;

	// Position of the light, in world-space
	_lightPosition = glm::vec3(10, 10, 0);

	_v_i = glm::vec3(0, 0, 0);

	// Create a game object
	float mass = 2.0f;




	for (int i = 0; i < 2; i++)
	{
		_physics_objects.push_back(new DynamicObject);
		_physics_objects[i]->SetVelocity(_v_i);
		_physics_objects[i]->SetMass(mass);
	}


	// Create a game level object
	for (int i = 0; i < 3; i++)
	{
		_scene_objects.push_back(new GameObject());
	}

	// Create the material for the game object- level
	Material *modelMaterial = new Material();
	// Shaders are now in files
	modelMaterial->LoadShaders("assets/shaders/VertShader.txt", "assets/shaders/FragShader.txt");
	// You can set some simple material properties, these values are passed to the shader
	// This colour modulates the texture colour
	modelMaterial->SetDiffuseColour(glm::vec3(0.8, 0.8, 0.8));
	// The material currently supports one texture
	// This is multiplied by all the light components (ambient, diffuse, specular)
	// Note that the diffuse colour set with the line above will be multiplied by the texture colour
	// If you want just the texture colour, use modelMaterial->SetDiffuseColour( glm::vec3(1,1,1) );
	modelMaterial->SetTexture("assets/textures/diffuse.bmp");
	// Need to tell the material the light's position
	// If you change the light's position you need to call this again
	modelMaterial->SetLightPosition(_lightPosition);
	// Tell the level object to use this material

	// The mesh is the geometry for the object
	Mesh *groundMesh = new Mesh();
	// Load from OBJ file. This must have triangulated geometry
	groundMesh->LoadOBJ("assets/models/cube.obj");
	// Tell the game object to use this mesh

	for each(GameObject* object in _scene_objects)
	{
		object->SetMaterial(modelMaterial);
		object->SetMesh(groundMesh);
		object->SetPosition(0.0f, 0.0f, 0.0f);
		object->SetRotation(3.141590f, 0.0f, 0.0f);
		object->SetVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
		object->SetScale(4.0f, 0.1f, 4.0f);
		object->SetType(1);
	}
	
	_scene_objects[1]->SetPosition(20.0f, -3.0f, 0.0f);
	_scene_objects[2]->SetPosition(-20.0f, -3.0f, 0.0f);

	// Create the material for the game object- level
	Material *objectMaterial = new Material();
	// Shaders are now in files
	objectMaterial->LoadShaders("assets/shaders/VertShader.txt", "assets/shaders/FragShader.txt");
	// You can set some simple material properties, these values are passed to the shader
	// This colour modulates the texture colour
	objectMaterial->SetDiffuseColour(glm::vec3(0.8, 0.1, 0.1));
	// The material currently supports one texture
	// This is multiplied by all the light components (ambient, diffuse, specular)
	// Note that the diffuse colour set with the line above will be multiplied by the texture colour
	// If you want just the texture colour, use modelMaterial->SetDiffuseColour( glm::vec3(1,1,1) );
	objectMaterial->SetTexture("assets/textures/default.bmp");
	// Need to tell the material the light's position
	// If you change the light's position you need to call this again
	objectMaterial->SetLightPosition(_lightPosition);

	// Set the geometry for the object
	Mesh *modelMesh = new Mesh();
	// Load from OBJ file. This must have triangulated geometry
	modelMesh->LoadOBJ("assets/models/sphere.obj");
	// Tell the game object to use this mesh
	glm::vec3 _i_p = glm::vec3(0.0f, 5.0f, 0.0f);
	glm::vec3 _i_s = glm::vec3(0.3f, 0.3f, 0.3f);

	for each(DynamicObject* object in _physics_objects)
	{
		object->SetMaterial(objectMaterial);
		object->SetMesh(modelMesh);
		_i_p += glm::vec3(0.5f, 1.0f, 0.0f);
		object->SetPosition(_i_p);
		object->SetScale(_i_s);
		object->SetBoundingRadius(0.35f);
		object->SetType(0);
	}

}

Scene::~Scene()
{
	// You should neatly clean everything up here
	for each(DynamicObject* object in _physics_objects)
		delete object;
	for each(GameObject* object in _scene_objects)
		delete object;
	delete _camera;
}

void Scene::Update(float deltaTs, Input* input)
{
	// Update the game object (this is currently hard-coded motion)
	if (input->cmd_x)
	{
		_simulation_start = true;
	}
	if (_simulation_start == true)
	{
		for each(DynamicObject* object in _physics_objects)
			object->StartSimulation(true);
	}
	if (input->cmd_q)
	{
		_physics_objects.push_back(new DynamicObject);
		_physics_objects.back()->SetVelocity(_v_i);
		_physics_objects.back()->SetMass(2.0f);

		Material *objectMaterial = new Material();
		objectMaterial->LoadShaders("assets/shaders/VertShader.txt", "assets/shaders/FragShader.txt");
		objectMaterial->SetDiffuseColour(glm::vec3(0.8, 0.1, 0.1));
		objectMaterial->SetTexture("assets/textures/default.bmp");
		objectMaterial->SetLightPosition(_lightPosition);

		Mesh *modelMesh = new Mesh();
		modelMesh->LoadOBJ("assets/models/sphere.obj");

		_physics_objects.back()->SetMaterial(objectMaterial);
		_physics_objects.back()->SetMesh(modelMesh);
	

		_physics_objects.back()->SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));
		_physics_objects.back()->SetScale(glm::vec3(0.3f,0.3f,0.3f));
		_physics_objects.back()->SetBoundingRadius(0.35f);
		_physics_objects.back()->SetType(0);
		_physics_objects.back()->SetVelocity(glm::vec3(2.0f, 1.0f, 0.0f));
	}
	
	for each(DynamicObject* object in _physics_objects)
		object->Update(deltaTs, _scene_objects, _physics_objects);
	for each(GameObject* object in _scene_objects)
		object->Update(deltaTs);
	_camera->Update(input);

	_viewMatrix = _camera->GetView();
	_projMatrix = _camera->GetProj();
														
}

void Scene::Draw()
{
	// Draw objects, giving the camera's position and projection
	for each(DynamicObject* object in _physics_objects)
		object->Draw(_viewMatrix, _projMatrix);
	for each(GameObject* object in _scene_objects)
		object->Draw(_viewMatrix, _projMatrix);

}


