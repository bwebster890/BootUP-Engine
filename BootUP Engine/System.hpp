#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "SystemID.h"
#include "Component.hpp"

class System
{
protected:
	unsigned m_id;

	bool m_enabled;

public:
	System()
	{
		m_id = SYS_NONE;
		m_enabled = false;
	}
	~System(){}

	virtual void Update() = 0{}
	virtual void AddComponent(std::string, Component* component) = 0{}

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