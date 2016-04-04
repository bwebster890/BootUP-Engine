#ifndef STATE_HPP
#define STATE_HPP

#include <string>

#include "RenderSystem.hpp"
#include "PhysicsSystem.hpp"

class State
{
private:
	std::vector <Component*> components;

	RenderSystem* m_render;
	PhysicsSystem* m_physics;

public:
	State();
	~State();

	void Update();

	void SetSystem(System*);
	void EnableSystem(unsigned);
	void DisableSystem(unsigned);

	void AddComponent(std::string, Component*);
	void ChangeComponent(std::string, Component*);
	void RemoveComponent(std::string, unsigned);

	void CopyEntity(std::string, std::string);
	void RemoveEntity(std::string);
};

#endif//STATE_HPP