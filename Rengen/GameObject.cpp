#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

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
}

void dae::GameObject::PostRender() const
{
	for (const auto& c : m_Components)
	{
		c->PostRender();
	}
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject> go)
{
	//THINK ABOUT POSITION

	if (m_Parent)
		m_Parent->m_Children.remove(this);

	m_Parent = go;

	if(go)
	go->m_Children.push_back(this);
}

void dae::GameObject::SetPosition(float x, float y, float z)
{
	m_LocalPosition = { x,y,z };
	m_GlobalPosFlag = true;
	for (auto& child : m_Children)
	{
		child->m_GlobalPosFlag = true;
	}
}

void dae::GameObject::SetPosition(glm::vec3 pos)
{
	SetPosition(pos.x, pos.y, pos.z);
}

glm::vec3 dae::GameObject::GetGlobalPos()
{
	if (m_IsMarkedForDeletion)
		return{ 0,0,0 };

	if (m_GlobalPosFlag)
	{
		glm::vec3 newPos{m_LocalPosition};
		std::shared_ptr<GameObject> current = this->m_Parent;

		while (current)
		{
			if (!current->m_GlobalPosFlag)
			{
				newPos += current->m_GlobalPosition;
				current = nullptr;
			}
			else
			{
				newPos += current->m_LocalPosition;
				current = current->m_Parent;
			}
		}

		m_GlobalPosition = newPos;
		m_GlobalPosFlag = false;
	}
	return m_GlobalPosition;
}

void dae::GameObject::remove()
{
	m_IsMarkedForDeletion = true;
}

bool dae::GameObject::GetIsMarkedForDeletion()
{
	return m_IsMarkedForDeletion;
}

