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


void dae::GameObject::SetParent(std::shared_ptr<GameObject> go)
{
	if (m_Parent)
		m_Parent->m_Children.remove(this);

	m_Parent = go;

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

glm::vec3 dae::GameObject::GetGlobalPos()
{
	
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

