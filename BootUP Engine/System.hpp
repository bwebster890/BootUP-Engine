#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "SystemID.h"
#include "Component.hpp"
#include <iostream>

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
	void ChangeComponent(std::string entity, Component* component)
	{
		for (unsigned i = 0; i < components.size(); i++)
		{
			if (components[i]->entity == entity && components[i]->id == component->id)
			{
				delete components[i];
				components[i] = component;
				break;
			}
		}
	}
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

	void CheckComponents(std::string entity)
	{
		for (unsigned i = 0; i < components.size(); i++)
		{
			if (components[i]->entity == entity)
			{
				std::cout << "Entity: " << components[i]->entity << " ID: " << components[i]->id << std::endl;
			}
		}
	}

	inline void Enable() {m_enabled = true;}
	inline void Disable(){m_enabled = false;}

	inline bool Enabled(){return m_enabled;}

	inline unsigned GetID(){return m_id;}
};

#endif//SYSTEM_HPP