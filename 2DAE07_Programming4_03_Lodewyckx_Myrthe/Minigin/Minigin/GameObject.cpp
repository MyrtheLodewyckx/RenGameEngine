#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(const float deltaTime)
{
	for (const auto& component : m_Components)
	{
		component->Update(deltaTime);
	}

}

void dae::GameObject::Render() const
{
	for (const auto& component : m_Components)
	{
		component->Render();
	}
}

void dae::GameObject::SetParent(GameObject* parent)
{
	m_Parent = parent;
}

size_t dae::GameObject::GetChildCount() const
{
	return m_Components.size();
}

decltype(auto) dae::GameObject::GetChildAt(int idx) const
{
	return m_Components[idx];
}
