#ifndef PHYSICS_SYSTEM_HPP
#define PHYSICS_SYSTEM_HPP

#include "System.hpp"
#include "Component.hpp"

class PhysicsSystem : public System
{
private:
	float worldGravity = 9.8;

	//components used in Update
	Position* m_position;
	Gravity* m_gravity;

public:
	PhysicsSystem();
	~PhysicsSystem();

	void Update();
	void AddComponent(Component*);
};

#endif//PHYSICS_SYSTEM_HPP