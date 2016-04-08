#ifndef PHYSICS_SYSTEM_HPP
#define PHYSICS_SYSTEM_HPP

#include "System.hpp"
#include "Component.hpp"

class PhysicsSystem : public System
{
private:
	float worldGravity = 9.8f;

	//components used in Update
	Orientation* m_orientation;
	Gravity* m_gravity;
	Velocity* m_velocity;

public:
	PhysicsSystem();
	virtual ~PhysicsSystem();

	void Update();
	void AddComponent(Component*);
};

#endif//PHYSICS_SYSTEM_HPP