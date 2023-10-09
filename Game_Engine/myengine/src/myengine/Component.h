#ifndef MYENGINE_COMPONENT_H
#define MYENGINE_COMPONENT_H

#include <memory>

#include "Entity.h"
#include "Enviroment.h"
#include "Keyboard.h"
#include "Core.h"

namespace myengine
{
	/**
	* Component a parent struct for all the components
	*/
	struct Component
	{
		std::shared_ptr<Entity> getEntity() { return m_entity.lock(); }
		std::shared_ptr<Core> getCore() { return m_entity.lock()->getCore(); }
		std::shared_ptr<Enviroment> getEnviroment() { return getCore()->getEnviroment(); }
		std::shared_ptr<Keyboard> getKeyboard() { return getCore()->getKeyboard(); }
		std::shared_ptr<Physics> getPhysics() { return getCore()->getPhysics(); }
		std::shared_ptr<Camera> getCamera() { return getCore()->getCamera(); }



	private:
		/**
		* onTick a virtual function for the child structs to run through
		*/
		virtual void onTick();
		/**
		* onDisplay a virtual function for the child structs to run through
		*/
		virtual void onDisplay();

		/**
		* tick a function to run through the onTick function
		*/
		void tick();
		/**
		* display a function to run through the onDisplay function
		*/
		void display();

		friend struct Entity;


		std::weak_ptr<Entity> m_entity; ///< pointer to entity that holds this component
	};
}

#endif