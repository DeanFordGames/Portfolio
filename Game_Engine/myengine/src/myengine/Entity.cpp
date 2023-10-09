#include "Entity.h"
#include "Component.h"

namespace myengine
{
	void Entity::tick()
	{//calls all tick functions in all components connected to this entity
		for (std::vector<std::shared_ptr<Component>>::iterator it = m_components.begin();
			it != m_components.end(); ++it)
		{
			(*it)->tick();
		}
	}

	void Entity::display()
	{//calls all display functions in all components connected to this entity
		for (std::vector<std::shared_ptr<Component>>::iterator it = m_components.begin();
			it != m_components.end(); ++it)
		{
			(*it)->display();
		}
	}

	void Entity::kill()
	{//flag to tell core this entity is dead
		if (!m_alive) return;

		m_alive = false;
	}

}