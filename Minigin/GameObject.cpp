#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject()
{
	for (Component* c : m_Components)
	{
		delete c;
		c = nullptr;
	}
}

void dae::GameObject::SetParent(GameObject* go)
{
	if (m_Parent)
		m_Parent->m_Children.remove(this);

	m_Parent = go;

	go->m_Children.push_back(this);
}

void dae::GameObject::Update(const float deltaTime)
{
	for (Component* c : m_Components)
	{
		c->Update(deltaTime);
	}

	for (Component* c : m_Components)
	{
		if (c->GetIsMarkedForDeletion() == true)
		{
			m_Components.remove(c);
			delete c;
			c = nullptr;
		}
	}
}

void dae::GameObject::FixedUpdate(const float fixedTimeStep)
{
	for (Component* c : m_Components)
	{
		c->FixedUpdate(fixedTimeStep);
	}
}

void dae::GameObject::Render() const
{
	for (const Component* c : m_Components)
	{
		c->Render();
	}
}

