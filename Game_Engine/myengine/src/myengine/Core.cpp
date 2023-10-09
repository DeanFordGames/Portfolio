#include "Core.h"
#include "Entity.h"

#include <AL/al.h>
#include <AL/alc.h>

#include <stdexcept>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <ws2tcpip.h>
#include <winsock2.h>

namespace myengine
{
	std::shared_ptr<Core> Core::initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();

		rtn->m_self = rtn;
		rtn->m_running = false;
		//create all extra objects
		rtn->m_enviroment = std::make_shared<Enviroment>();
		rtn->m_resources = std::make_shared<Resources>();
		rtn->m_physics = std::make_shared<Physics>();
		rtn->m_keyboard = std::make_shared<Keyboard>();
		rtn->m_camera = std::make_shared<Camera>();

		//initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw std::runtime_error("Failed to initialize SDL");
		}
		//create window
		if (!(rtn->m_window = SDL_CreateWindow("SLD2 Platform",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			INITIAL_WIDTH, INITIAL_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)))
		{
			SDL_Quit();
			throw std::runtime_error("Failed to create window");
		}
		//create context 
		if (!(rtn->m_context = SDL_GL_CreateContext(rtn->m_window)))
		{
			SDL_DestroyWindow(rtn->m_window);
			SDL_Quit();
			throw std::runtime_error("Failed to create OpenGl context");
		}


		//set up audio
		ALCdevice* device = alcOpenDevice(NULL);

		if (!device)
		{
			throw std::runtime_error("Failed to open audio device");
		}

		ALCcontext* context = alcCreateContext(device, NULL);

		if (!context)
		{
			alcCloseDevice(device);
			throw std::runtime_error("Failed to create audio context");
		}

		if (!alcMakeContextCurrent(context))
		{
			alcDestroyContext(context);
			alcCloseDevice(device);
			throw std::runtime_error("Failed to make context current");
		}

		alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
		//alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);

		//ircComponent setup
		WSADATA wsaData;

		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

		if (iResult != 0)
		{
			throw std::runtime_error("WSAStartup failed");
		}


		return rtn;
	}

	Core::~Core()
	{
		SDL_GL_DeleteContext(m_context);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}


	void Core::start()
	{
		SDL_Event event = { 0 };
		m_running = true;
		//set mouse invisible and center of screen
		SDL_SetRelativeMouseMode(SDL_bool::SDL_TRUE);

		while (m_running)
		{
			while (SDL_PollEvent(&event))
			{//when windows closed close loop
				if (event.type == SDL_QUIT)
				{
					m_running = false;
				}
				else if (event.type == SDL_KEYDOWN)//key events
				{
					m_keyboard->setKeyDown(event.key.keysym.sym);
				}
				else if (event.type == SDL_KEYUP)
				{
					m_keyboard->setKeyUp(event.key.keysym.sym);
				}
				else if (event.type = SDL_MOUSEMOTION)//mouse events
				{
					int x = 0;
					int y = 0;
					SDL_GetRelativeMouseState(&x, &y);
					m_keyboard->setMouseMovement(x, y);
				}
			}

			//call all tick functions for entities and extra structs
			m_enviroment->tick();
			m_physics->tick();
			m_camera->tick();

			//changed because iterator doesnt like adding entities
			//for (auto it = m_entities.begin(); //auto = std::vector<std::shared_ptr<Entity> >::iterator
			//	it != m_entities.end(); ++it)
			//{
			//	(*it)->tick();
			//}

			for (int i = 0; i < m_entities.size(); i++)
			{
				m_entities.at(i)->tick();
			}

			auto itr = m_entities.begin();
			while (itr != m_entities.end())
			{
				if ((*itr)->alive())
				{
					itr++;
				}
				else
				{
					itr = m_entities.erase(itr);
				}
			}

			//clear all rendering before rendering next frame
			rend::Renderer r(INITIAL_WIDTH, INITIAL_HEIGHT);
			r.clear();
			//call all diplay functions for each entity
			for (auto it = m_entities.begin(); //auto = std::list<std::shared_ptr<Entity> >::iterator
				it != m_entities.end(); ++it)
			{
				(*it)->display();
			}
			//swap frame buffer
			SDL_GL_SwapWindow(m_window);


		}
	}

	void Core::stop()
	{
		m_running = false;
	}

	std::shared_ptr<Entity> Core::addEntity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();

		rtn->m_self = rtn;

		rtn->m_core = m_self;

		m_entities.push_back(rtn);

		return rtn;
	}

}