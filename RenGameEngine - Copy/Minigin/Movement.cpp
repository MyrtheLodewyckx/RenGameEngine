#include "MiniginPCH.h"
#include "Movement.h"
#include "GameObject.h"
#include "Transform.h"

void dae::Movement::MoveHorizontally(const float deltaTime, const int speed, Transform* transform)
{
	transform->SetPosition(transform->GetPosition().x + (speed * deltaTime), transform->GetPosition().y, transform->GetPosition().z);
}

void dae::Movement::MoveVertically(const float deltaTime, const int speed, Transform* transform)
{
	transform->SetPosition(transform->GetPosition().x, transform->GetPosition().y - (speed * deltaTime), transform->GetPosition().z);
}

