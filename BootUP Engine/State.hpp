#ifndef STATE_HPP
#define STATE_HPP

#include <string>

#include "RenderSystem.hpp"

class State
{
private:
	std::vector <Component*> components;

	RenderSystem* m_render;

public:
	State();
	~State();

	void Update();

	void SetSystem(System*);
	void EnableSystem(unsigned);
	void DisableSystem(unsigned);

	void AddComponent(std::string, Component*);
	void RemoveComponent(std::string, unsigned);

	void CopyEntity(std::string, std::string);
};

#endif//STATE_HPP