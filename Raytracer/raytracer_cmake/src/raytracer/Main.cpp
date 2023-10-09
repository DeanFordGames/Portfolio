#include <cmath>
#include <vector>
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

#include "MCG_GFX_Lib.h"

#include "Camera.h"
#include "Ray.h"
#include "Tracer.h"
#include "Light.h"

std::mutex mtx1;
std::mutex mtx2;

Tracer setScene()
{
	Tracer tracer = Tracer();

	tracer.addSphere();
	tracer.m_objects[0].m_centre = glm::vec3(1.5f, 0.0f, -10.0f);
	tracer.m_objects[0].m_surfaceColour = glm::vec3(0.3f, 1.0f, 0.3f);
	tracer.m_objects[0].m_roughness = 0.6f;
	tracer.addSphere();
	tracer.m_objects[1].m_centre = glm::vec3(-1.5f, 0.0f, -10.0f);
	tracer.m_objects[1].m_surfaceColour = glm::vec3(0.3f, 0.3f, 1.0f);
	tracer.m_objects[1].m_roughness = 0.5f;
	tracer.addSphere();
	tracer.m_objects[2].m_centre = glm::vec3(0.0f, 101.0f, -10.0f);
	tracer.m_objects[2].m_surfaceColour = glm::vec3(1.0f, 0.3f, 0.3f);
	tracer.m_objects[2].m_roughness = 0.8f;
	tracer.m_objects[2].m_radius = 100.0f;
	tracer.addSphere();
	tracer.m_objects[3].m_centre = glm::vec3(0.0f, -1.5f, -10.0f);
	tracer.m_objects[3].m_surfaceColour = glm::vec3(0.3f, 0.3f, 0.3f);
	tracer.m_objects[3].m_roughness = 0.4f;
	tracer.addSphere();
	tracer.m_objects[4].m_centre = glm::vec3(1.7f, -2.0f, -10.0f);
	tracer.m_objects[4].m_surfaceColour = glm::vec3(0.6f, 0.4f, 0.8f);
	tracer.m_objects[4].m_roughness = 0.1f;
	tracer.m_objects[4].m_radius = 0.6f;
	tracer.addSphere();
	tracer.m_objects[5].m_centre = glm::vec3(-1.7f, -2.0f, -10.0f);
	tracer.m_objects[5].m_surfaceColour = glm::vec3(0.1f, 0.6f, 0.8f);
	tracer.m_objects[5].m_roughness = 0.3f;
	tracer.m_objects[5].m_radius = 0.6f;

	return tracer;
}

void threadLoop(std::vector<int>* _jobs, Camera _cam, Tracer _tracer, Light _light, glm::ivec2 _windowSize, const int _numberOfSamples, const int _maxBounces)
{
	//lock job list for a thread to access
	mtx1.lock();
	while (!_jobs->empty()) {
		//get next job(the x coordinate on the screen)
		int x = _jobs->at(0);
		_jobs->erase(_jobs->begin());
		//unlcok job list for next thread to use
		mtx1.unlock();

		for (int y = 0; y < _windowSize.y; y++)
		{
			glm::vec3 pixelColour = glm::vec3(0.0f);
			// Preparing a position to draw a pixel
			glm::ivec2 pixelPosition = glm::ivec2(x, y);
			//create a ray and colour for each sample
			for (int s = 0; s < _numberOfSamples; s++)
			{
				Ray ray = _cam.returnRay(pixelPosition, _windowSize);
				pixelColour += _tracer.returnColour(ray, _light, _maxBounces);
			}
			//divice pixel colour by samples to get an average pixel colour
			pixelColour /= _numberOfSamples;

			mtx2.lock();
			// Draws a single pixel at the specified coordinates in the specified colour
			MCG::DrawPixel(pixelPosition, pixelColour);
			mtx2.unlock();
		}
		mtx2.lock();
		//print all pixels that have been processed so far
		MCG::ProcessFrame();
		mtx2.unlock();

		mtx1.lock();
	}
	mtx1.unlock();
}

int main( int argc, char *argv[] )
{
	// Variable for storing window dimensions
	//glm::ivec2 windowSize( 640, 480 );
	//glm::ivec2 windowSize( 1280, 720 );
	glm::ivec2 windowSize( 1280, 960 );
	//glm::ivec2 windowSize( 1920, 1080 );

	//allow user to input how many threads they want to use
	std::cout << "Choose number of threads: ";
	int input;
	std::cin >> input;

	auto time = std::chrono::high_resolution_clock::now();

	if (input == 0)
	{
		std::cout << "Changing to 1 thread......thanks" << std::endl;
		input = 1;
	}
	const int threadNumber = input;

	// Call MCG::Init to initialise and create your window
	// Tell it what size you want the window to be
	if( !MCG::Init( windowSize ) )
	{
		// We must check if something went wrong
		// (this is very unlikely)
		return -1;
	}

	// Sets every pixel to the same colour
	// parameters are RGB, numbers are from 0 to 1
	MCG::SetBackground( glm::vec3(0,0,0) );

	// Preparing a colour to draw
	// Colours are RGB, each value ranges between 0 and 1
	glm::vec3 pixelColour( 0.0f, 0.0f, 0.0f );

	//create thread array
	std::thread* threads = new std::thread[threadNumber];
	//create job list for threads to work through
	std::vector<int>* jobs = new std::vector<int>;
	for (int x = 0; x < windowSize.x; x++)
	{
		jobs->push_back(x);
	}

	// set up all classes and objects in scene
	Camera cam = Camera();
	Tracer tracer = setScene();
	Light light = Light();

	const int maxBounces = 30;
	const int numberOfSamples = 100;

	//initalize the threads function with variables to pass through
	for (int i = 0; i < threadNumber; i++)
	{
		threads[i] = std::thread(threadLoop, jobs, cam, tracer, light, windowSize, numberOfSamples, maxBounces);
	}
	//start all threads
	for (int i = 0; i < threadNumber; i++)
	{
		threads[i].join();
	}

	auto currentTime = std::chrono::high_resolution_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - time).count() << " ms" << std::endl;

	// Displays drawing to screen and holds until user closes window
	// You must call this after all your drawing calls
	// Program will exit after this line
	return MCG::ShowAndHold();

	return 0;
	
	

}