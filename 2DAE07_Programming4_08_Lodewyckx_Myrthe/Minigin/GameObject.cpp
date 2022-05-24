#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <memory>

dae::GameObject::~GameObject()
{
	/*delete m_Parent;
	m_Parent = nullptr;

	for (auto go : m_Children)
	{
		delete go;
		go = nullptr;
	}*/
}

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
	m_Parent->m_Children.push_back(this);
}

void dae::GameObject::RemoveParent()
{
	m_Parent = nullptr;
}

size_t dae::GameObject::GetChildCount() const
{
	return m_Components.size();
}

dae::GameObject* dae::GameObject::GetChildAt(int idx)
{
	return m_Children[idx];
}
