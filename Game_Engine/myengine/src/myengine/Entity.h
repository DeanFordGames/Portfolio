#ifndef MYENGINE_ENTITY_H
#define MYENGINE_ENTITY_H


#include <memory>
#include <vector>
#include <stdexcept>

namespace myengine
{
	struct Component;
	struct Core;
	/**
	* Entity struct for all the objects in the scene
	*/
	struct Entity
	{
		/**
		* addComponent adds a component to component vector of typename T
		* \return returns the added component
		*/
		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();
			rtn->m_entity = m_self;
			m_components.push_back(rtn);

			return rtn;
		}
		/**
		* getComponent searches through all components in entity
		* \return returns the required component
		*/
		template <typename T>
		std::shared_ptr<T> getComponent()
		{
			for (std::vector<std::shared_ptr<Component>>::iterator it = m_components.begin();
				it != m_components.end(); ++it)
			{
				std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>((*it));
				if (rtn)
				{
					return rtn;
				}
			}
			throw std::runtime_error("Specified component not found");
			
		}


		std::shared_ptr<Core> getCore() { return m_core.lock(); }

		/**
		* Entity initalize entity as alive
		*/
		Entity() { 
			m_alive = true; 
		}

		bool alive() { return m_alive; }

		/**
		* tick update function for all entities
		*/
		void tick();
		/**
		* display update graphics function for all entities
		*/
		void display();
		/**
		* kill clean up entity when killed
		*/
		void kill();

	private:
		std::vector<std::shared_ptr<Component> > m_components; ///< vector of entities component

		bool m_alive; ///< check if entity is still alive

		std::weak_ptr<Entity> m_self; ///< pointer to itself
		std::weak_ptr<Core> m_core; ///< pointer to core

		friend struct Core;
	};

}

#endif