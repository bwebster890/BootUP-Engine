#include "State.hpp"

State::State()
{
	m_render = nullptr;
}
State::~State()
{
	for (std::map <std::string, std::map<unsigned, Component*>>::iterator i = components.begin(); i != components.end(); i++)
	{
		for (int j = 0; j < components[i->first].size(); j++)
		{
			delete components[i->first][j];
		}
	}
}

void State::Update()
{
	m_render->Update();
}

void State::SetSystem(System* system)
{
	system->Enable();

	if (system->GetID() == SYS_RENDER)
		m_render = dynamic_cast<RenderSystem*>(system);
}
void State::EnableSystem(unsigned id)
{
	if (id = m_render->GetID())
		m_render->Enable();
}
void State::DisableSystem(unsigned id)
{
	if (id = m_render->GetID())
		m_render->Disable();
}

void State::AddComponent(std::string entity, Component* component)
{
	components[entity][component->id] = component;

	if (component->id == COMP_POS)
	{
		m_render->AddComponent(entity, component);
	}

	if (component->id == COMP_RECT)
	{
		m_render->AddComponent(entity, component);
	}

	if (component->id == COMP_TEXTURE)
	{
		m_render->AddComponent(entity, component);
	}
}
Component* State::GetComponent(std::string entity, unsigned id)
{
	return components[entity][id];
}