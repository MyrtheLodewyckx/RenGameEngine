#include "MiniginPCH.h"
#include "Transform.h"

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	SetPosition(glm::vec3(x, y, z));

}

void dae::Transform::SetPosition(glm::vec3 pos)
{

	m_Position = pos;
	

	auto parent = m_Go->GetParent();
	if (parent)
		m_Position = pos + m_LocalPosition;
	else
		m_LocalPosition = m_Position = pos;

	m_HitBox.x = (int)m_Position.x;
	m_HitBox.y = (int)m_Position.y;
}

void dae::Transform::SetLocalPosition(float x, float y, float z)
{
	SetLocalPosition(glm::vec3(x,y,z));
}

void dae::Transform::SetLocalPosition(glm::vec3 pos)
{
	auto parent = m_Go->GetParent();
	if (!parent)
		m_Position = m_LocalPosition = pos;
	else
	{
		m_Position -= m_LocalPosition + pos;
		m_LocalPosition = pos;
	}

}

void dae::Transform::SetDimentions(float width, float height)
{
	m_HitBox.w = (int)width;
	m_HitBox.h = (int)height;
}
