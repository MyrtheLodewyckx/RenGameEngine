#include "RotateComponent.h"
#include "GameObject.h"
#include <chrono>



void RotateComponent::Update(const float deltaTime)
{
	const float speed{ 3.f };
	elapsedTime += deltaTime;
	glm::vec3 pos{};
	if (!m_RotateClockWise)
	pos = {cos(-elapsedTime*speed)* m_Rad,sin(-elapsedTime*speed)*m_Rad,0};
	else 
	pos = { cos(elapsedTime*speed) * m_Rad,sin(elapsedTime*speed) * m_Rad,0 };

	pos += m_RotatePoint;
	
	

	m_GameObject->SetPosition(pos.x, pos.y, pos.z);
}

void RotateComponent::SetRotationPoint(glm::vec3 p)
{
	m_RotatePoint = p;
}

void RotateComponent::RotateClockWise(bool b)
{
	m_RotateClockWise = b;
}

void RotateComponent::SetRadius(float rad)
{
	m_Rad = rad;
}