#include "State.hpp"

State::State()
{
	m_render = nullptr;
	m_physics = nullptr;
}
State::~State()
{
	for (unsigned i = 0; i < components.size(); i++)
	{
		delete (components[i]);
		components.erase(components.begin() + i);
	}
}

void State::Update()
{
	if (m_render->Enabled())
		m_render->Update();
	if (m_physics->Enabled())
		m_physics->Update();
}

void State::SetSystem(System* system)
{
	if (system->GetID() == SYS_RENDER)
		m_render = dynamic_cast<RenderSystem*>(system);
	if (system->GetID() == SYS_PHYSICS)
		m_physics = dynamic_cast<PhysicsSystem*>(system);
}
void State::EnableSystem(unsigned id)
{
	if (id = m_render->GetID())
		m_render->Enable();
	if (id = m_physics->GetID())
		m_physics->Enable();
}
void State::DisableSystem(unsigned id)
{
	if (id = m_render->GetID())
		m_render->Disable();
	if (id = m_physics->GetID())
		m_physics->Disable();
}

void State::AddComponent(std::string entity, Component* component)
{
	component->entity = entity;
	components.push_back(component);

	if (component->id == COMP_POS)
	{
		m_render->AddComponent(component);
		m_physics->AddComponent(component);
	}

	if (component->id == COMP_RECT)
	{
		m_render->AddComponent(component);
	}

	if (component->id == COMP_TEXTURE)
	{
		m_render->AddComponent(component);
	}
	if (component->id == COMP_GRAVITY)
	{
		m_physics->AddComponent(component);
	}
	if (component->id == COMP_VELOCITY)
	{
		m_physics->AddComponent(component);
	}
}
void State::ChangeComponent(std::string entity, Component* component)
{
	component->entity = entity;

	for (unsigned i = 0; i < components.size(); i++)
	{
		if (components[i]->entity == entity && components[i]->id == component->id)
			components[i] = component;
	}

	if (component->id == COMP_POS)
	{
		m_render->ChangeComponent(entity, component);
		m_physics->ChangeComponent(entity, component);
	}

	if (component->id == COMP_RECT)
	{
		m_render->ChangeComponent(entity, component);
	}

	if (component->id == COMP_TEXTURE)
	{
		m_render->ChangeComponent(entity, component);
	}
	if (component->id == COMP_GRAVITY)
	{
		m_physics->ChangeComponent(entity, component);
	}
	if (component->id == COMP_VELOCITY)
	{
		m_physics->ChangeComponent(entity, component);
	}
}
void State::RemoveComponent(std::string entity, unsigned id)
{
	for (unsigned i = 0; i < components.size(); i++)
	{
		if (components[i]->entity == entity && components[i]->id == id)
		{
			if (components[i]->id == COMP_POS)
			{
				m_render->RemoveComponent(entity, id);
				m_physics->RemoveComponent(entity, id);
			}

			if (components[i]->id == COMP_RECT)
			{
				m_render->RemoveComponent(entity, id);
			}

			if (components[i]->id == COMP_TEXTURE)
			{
				m_render->RemoveComponent(entity, id);
			}
			if (components[i]->id == COMP_GRAVITY)
			{
				m_physics->RemoveComponent(entity, id);
			}
			if (components[i]->id == COMP_VELOCITY)
			{
				m_physics->RemoveComponent(entity, id);
			}

			delete components[i];
			components.erase(components.begin() + i);
		}
	}
}

void State::CopyEntity(std::string old_entity, std::string new_entity)
{
	for (unsigned i = 0; i < components.size(); i++)
	{
		if (components[i]->entity == old_entity)
		{
			if (components[i]->id == COMP_POS)
			{
				AddComponent(new_entity, new Position(*dynamic_cast<Position*>(components[i])));
			}

			if (components[i]->id == COMP_RECT)
			{
				AddComponent(new_entity, new Rect(*dynamic_cast<Rect*>(components[i])));
			}

			if (components[i]->id == COMP_TEXTURE)
			{
				AddComponent(new_entity, new Texture(*dynamic_cast<Texture*>(components[i])));
			}
			if (components[i]->id == COMP_GRAVITY)
			{
				AddComponent(new_entity, new Gravity(*dynamic_cast<Gravity*>(components[i])));
			}
			if (components[i]->id == COMP_VELOCITY)
			{
				AddComponent(new_entity, new Velocity(*dynamic_cast<Velocity*>(components[i])));
			}
		}
	}
}
void State::RemoveEntity(std::string entity)
{
	for (unsigned i = 0; i < components.size();)
	{
		if (components[i]->entity == entity)
		{
			if (components[i]->id == COMP_POS)
			{
				m_render->RemoveComponent(entity, components[i]->id);
				m_physics->RemoveComponent(entity, components[i]->id);
			}

			if (components[i]->id == COMP_RECT)
			{
				m_render->RemoveComponent(entity, components[i]->id);
			}

			if (components[i]->id == COMP_TEXTURE)
			{
				m_render->RemoveComponent(entity, components[i]->id);
			}

			if (components[i]->id == COMP_GRAVITY)
			{
				m_physics->RemoveComponent(entity, components[i]->id);
			}
			if (components[i]->id == COMP_VELOCITY)
			{
				m_physics->RemoveComponent(entity, components[i]->id);
			}

			delete components[i];
			components.erase(components.begin() + i);
		}
		else
			++i;
	}
}