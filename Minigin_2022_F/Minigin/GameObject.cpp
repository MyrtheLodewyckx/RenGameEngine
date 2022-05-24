#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"



dae::GameObject::GameObject()
	:m_Parent{NULL}
{
}


dae::GameObject::~GameObject() = default;


void dae::GameObject::Update(const float deltaTime)
{
	for (std::shared_ptr<Component> component : m_Components)
	{
		component->Update(deltaTime);
	}
}


void dae::GameObject::Render() const
{
	for (std::shared_ptr<Component> component : m_Components)
	{
		component->Render();
	}
}

void dae::GameObject::SetParent(GameObject* parent)
{
	m_Parent = parent;
}

decltype(auto) dae::GameObject::GetParent()
{
	return m_Parent;
}


size_t dae::GameObject::GetChildCount() const
{
	return m_Children.size();
}

decltype(auto) dae::GameObject::GetChildAt(int idx) const
{
	return m_Children[idx];
}

void dae::GameObject::RemoveChild(int idx)
{
	m_Children.erase(m_Children.begin()+idx);
}

void dae::GameObject::AddChild(GameObject* child)
{
	m_Children.push_back(child);
}


