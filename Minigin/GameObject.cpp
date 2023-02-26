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

void dae::GameObject::Update(const float deltaTime)
{
	for (Component* c : m_Components)
	{
		c->Update(deltaTime);
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

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

glm::vec3 dae::GameObject::GetWorldPosition()
{
	return m_transform.GetPosition();
}
