#ifndef STATE_HPP
#define STATE_HPP

#include <map>
#include <string>

#include "RenderSystem.hpp"

class State
{
private:
	std::map <std::string, std::map<unsigned, Component*>> components;

	RenderSystem* m_render;

public:
	State();
	~State();

	void Update();

	void SetSystem(System*);
	void EnableSystem(unsigned);
	void DisableSystem(unsigned);

	void AddComponent(std::string, Component*);
	Component* GetComponent(std::string, unsigned);
};

#endif//STATE_HPP