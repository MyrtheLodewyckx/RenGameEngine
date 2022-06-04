#include "MiniginPCH.h"
#include "Transform.h"

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	SetPosition(glm::vec3(x, y, z));

}

void dae::Transform::SetPosition(glm::vec3 pos)
{
	m_Position = pos;
	m_HitBox.x = (int)pos.x;
	m_HitBox.y = (int)pos.y;
	/*if (m_Go->GetParent())
	{
		auto p = m_Go->GetParent();
		m_LocalPosition = m_Position - p->GetComponent<Transform>()->GetPosition();
	}*/
}

void dae::Transform::SetDimentions(float width, float height)
{
	m_HitBox.w = (int)width;
	m_HitBox.h = (int)height;
}
