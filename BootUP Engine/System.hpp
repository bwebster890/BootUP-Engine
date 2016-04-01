#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "SystemID.h"
#include "Component.hpp"

class System
{
protected:
	unsigned m_id;
	bool m_enabled;

	std::vector <Component*> components;

public:
	System()
	{
		m_id = SYS_NONE;
		m_enabled = false;
	}
	~System(){}

	virtual void Update() = 0{}
	virtual void AddComponent(Component* component) = 0{}
	void RemoveComponent(std::string entity, unsigned id)
	{
		for (unsigned i = 0; i < components.size(); i++)
		{
			if (components[i]->entity == entity && components[i]->id == id)
			{
				components.erase(components.begin() + i);
			}
		}
	}

	void Enable() 
	{
		m_enabled = true;
	}
	void Disable()
	{
		m_enabled = false;
	}

	unsigned GetID()
	{
		return m_id;
	}
};

#endif//SYSTEM_HPP