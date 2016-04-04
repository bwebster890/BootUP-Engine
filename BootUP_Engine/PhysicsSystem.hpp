#ifndef PHYSICS_SYSTEM_HPP
#define PHYSICS_SYSTEM_HPP

#include "System.hpp"
#include "Component.hpp"

class PhysicsSystem : public System
{
private:
	float worldGravity = 9.8f;

	//components used in Update
	Position* m_position;
	Gravity* m_gravity;
	Velocity* m_velocity;

public:
	PhysicsSystem();
	~PhysicsSystem();

	void Update();
	void AddComponent(Component*);
};

#endif//PHYSICS_SYSTEM_HPP