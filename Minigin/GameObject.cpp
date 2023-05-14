#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

<<<<<<< Updated upstream
dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(){}

void dae::GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
=======
dae::GameObject::~GameObject()
{
}

void dae::GameObject::Initialize()
{

	for (const auto& c : m_Components)
	{
		c->Initialize();
	}

}

void dae::GameObject::Update(const float deltaTime)
{
	for (const auto& c : m_Components)
	{
		c->Update(deltaTime);
	}

	for (const auto& c : m_Components)
	{
		if (c->GetIsMarkedForDeletion() == true)
		{
			m_Components.remove(c);
		}
	}
}

void dae::GameObject::FixedUpdate(const float fixedTimeStep)
{
	for (const auto& c : m_Components)
	{
		c->FixedUpdate(fixedTimeStep);
	}
}

void dae::GameObject::Render() const
{
	for (const auto& c : m_Components)
	{
		c->Render();
	}
>>>>>>> Stashed changes
}

void dae::GameObject::SetTexture(const std::string& filename)
{
<<<<<<< Updated upstream
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
=======
	//THINK ABOUT POSITION

	if (m_Parent)
		m_Parent->m_Children.remove(this);

	m_Parent = go;

	if(go)
	go->m_Children.push_back(this);
>>>>>>> Stashed changes
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
