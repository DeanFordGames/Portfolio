#ifndef MYENGINE_CORE_H
#define MYENGINE_CORE_H

#include <memory>
#include <list>
#include <SDL2/SDL.h>
#include <AL/al.h>
#include <AL/alc.h>

#include "Keyboard.h"
#include "Enviroment.h"
#include "Resources.h"
#include "Physics.h"
#include "Camera.h"

#include <rend/rend.h>

#define INITIAL_HEIGHT 480
#define INITIAL_WIDTH 640

namespace myengine
{
	struct Entity;
	/**
	* Core the main controller of the program. holds the main loop.
	*/
	struct Core
	{
		/**
		* initialize initalises the scene including window, enviroment, keyboard, resource
		*/
		static std::shared_ptr<Core> initialize();

		~Core();

		/**
		* start main game loop
		*/
		void start();
		/**
		* stop clean up when closing
		*/
		void stop();

		/**
		* addEntity add an entity to the list
		*/
		std::shared_ptr<Entity> addEntity();


		std::shared_ptr<Enviroment> getEnviroment() { return m_enviroment; }
		std::shared_ptr<Keyboard> getKeyboard() { return m_keyboard; }
		std::shared_ptr<Resources> getResources() { return m_resources; }
		std::shared_ptr<Physics> getPhysics() { return m_physics; }
		std::shared_ptr<Camera> getCamera() { return m_camera; }

		/**
		* find all components of a certain type
		* \param _out a vector that holds all found components
		*/
		template <typename T>
		void find(std::vector<std::shared_ptr<T>>& _out)
		{
			for (size_t ei = 0; ei < m_entities.size(); ++ei)
			{
				std::shared_ptr<Entity> e = m_entities.at(ei);

				for (size_t ci = 0; ci < e->m_components.size(); ++ci)
				{
					std::shared_ptr<Component> c = e->m_components.at(ci);

					std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(c);

					if (t)
						_out.push_back(t);
				}
			}
		}

	private:
		bool m_running; ///< to check if the program is still running
		std::vector<std::shared_ptr<Entity> > m_entities; ///< list off all entities in scene
		std::shared_ptr<Keyboard> m_keyboard; ///< pointer to keyboard struct
		std::shared_ptr<Enviroment> m_enviroment; ///< pointer to enviroment
		std::shared_ptr<Resources> m_resources; ///< pointer to all resources
		std::shared_ptr<Physics> m_physics; ///< pointer to the world physics
		std::shared_ptr<Camera> m_camera;

		std::weak_ptr<Core> m_self; ///< pointer to its self

		SDL_Window* m_window; ///< pointer to window
		SDL_GLContext m_context; ///< holds window context
	};

}

#endif // !MYENGINE_CORE_H