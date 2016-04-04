#include <glew/glew.h>

#include "PhysicsSystem.hpp"

PhysicsSystem::PhysicsSystem()
{
	m_id = SYS_PHYSICS;
	m_enabled = true;
}
PhysicsSystem::~PhysicsSystem()
{

}

void PhysicsSystem::Update()
{
	for (unsigned i = 0; i < components.size(); i++)
	{
		if (components[i]->id == COMP_GRAVITY)
		{
			m_position = nullptr;

			// Set entity string to make sure the system updates the right entities position
			std::string myEntity = components[i]->entity;
			for (unsigned j = 0; j < components.size(); j++)
			{
				if (components[j]->entity == myEntity)
				{
					if (components[j]->id == COMP_POS)
					{
						m_position = dynamic_cast<Position*>(components[j]);
						j = components.size();
					}
				}
			}
			// If the entitiy has position apply gravity.
			if (m_position != nullptr)
			{
				float appliedGravity = 0.0;
				m_gravity = dynamic_cast<Gravity*>(components[i]);
				if (m_gravity->customGravity == 0.0)
				{
					appliedGravity = worldGravity;
				}
				else
				{
					appliedGravity = m_gravity->customGravity;
				}
				// Apply Gravity
				m_position->y += appliedGravity;
			}
		}
		if (components[i]->id == COMP_VELOCITY)
		{
			m_position = nullptr;

			// Set entity string to make sure the system updates the right entities position
			std::string myEntity = components[i]->entity;
			for (unsigned j = 0; j < components.size(); j++)
			{
				if (components[j]->entity == myEntity)
				{
					if (components[j]->id == COMP_POS)
					{
						m_position = dynamic_cast<Position*>(components[j]);
						j = components.size();
					}
				}
			}
			// If the entitiy has position apply velocity.
			if (m_position != nullptr)
			{
				m_velocity = dynamic_cast<Velocity*>(components[i]);
				
				// Apply Velocity
				m_position->x += m_velocity->x;
				m_position->y += m_velocity->y;
				m_position->z += m_velocity->z;
			}
		}
	}
}
void PhysicsSystem::AddComponent(Component* component)
{
	components.push_back(component);

	if (component->id == COMP_POS) {}
	if (component->id == COMP_GRAVITY) {}
}