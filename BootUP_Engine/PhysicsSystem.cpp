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
			m_orientation = nullptr;

			// Set entity string to make sure the system updates the right entities orientation
			std::string myEntity = components[i]->entity;
			for (unsigned j = 0; j < components.size(); j++)
			{
				if (components[j]->entity == myEntity)
				{
					if (components[j]->id == COMP_ORI)
					{
						m_orientation = dynamic_cast<Orientation*>(components[j]);
						j = components.size();
					}
				}
			}
			// If the entitiy has orientation apply gravity.
			if (m_orientation != nullptr)
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
				m_orientation->adjustPosition(glm::vec3(0.0, appliedGravity, 0.0));
			}
		}
		if (components[i]->id == COMP_VELOCITY)
		{
			m_orientation = nullptr;

			// Set entity string to make sure the system updates the right entities orientation
			std::string myEntity = components[i]->entity;
			for (unsigned j = 0; j < components.size(); j++)
			{
				if (components[j]->entity == myEntity)
				{
					if (components[j]->id == COMP_ORI)
					{
						m_orientation = dynamic_cast<Orientation*>(components[j]);
						j = components.size();
					}
				}
			}
			// If the entitiy has orientation apply velocity.
			if (m_orientation != nullptr)
			{
				m_velocity = dynamic_cast<Velocity*>(components[i]);
				
				// Apply Velocity
				m_orientation->adjustPosition(m_velocity->velocity);
			}
		}
	}
}
void PhysicsSystem::AddComponent(Component* component)
{
	components.push_back(component);

	if (component->id == COMP_ORI) {}
	if (component->id == COMP_GRAVITY) {}
}