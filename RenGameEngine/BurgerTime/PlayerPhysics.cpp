#include "pch.h"
#include "PlayerPhysics.h"
#include "InputManager.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Movement.h"
#include "Enemy.h"
#include "Collision.h"

std::vector<dae::PlayerPhysics*> dae::PlayerPhysics::m_ObjectList;

dae::PlayerPhysics::PlayerPhysics(GameObject* go) : Physics(go) 
{
	m_IsOnGround = true;
	m_ObjectList.push_back(this);
}

dae::PlayerPhysics::~PlayerPhysics()
{
	auto newEnd = std::remove(m_ObjectList.begin(), m_ObjectList.end(), this);
	m_ObjectList.erase(newEnd, m_ObjectList.end());
}

void dae::PlayerPhysics::Update(const float)
{
}

dae::PlayerPhysics* dae::PlayerPhysics::GetPlayer(int playerIdx)
{
	for (auto player : m_ObjectList)
	{
		if (player->m_PlayerIdx == playerIdx)
			return player;
	}
	return nullptr;
}

SDL_Rect dae::PlayerPhysics::GetHitBox()
{
	if (m_pTransform)
		return SDL_Rect(m_pTransform->GetHitBox());
	else return SDL_Rect(0, 0, 0, 0);
}


glm::vec3 dae::PlayerPhysics::GetPos()
{
	if (m_pTransform)
		return m_pTransform->GetPosition();
	else return glm::vec3(0, 0, 0);
}

void dae::PlayerPhysics::SetPos(glm::vec3 pos)
{
	m_pTransform->SetPosition(pos);
}

void dae::PlayerPhysics::HandleMovement(const float deltaTime)
{
	const int horizontalSpeed{ 100 };
	const int verticalSpeed{ 60 };
	Movement movement;

	auto j = InputManager::GetInstance().GetPlayerDirection(m_PlayerIdx);

	if (!m_pTransform)
		m_pTransform = m_Go->GetComponent<Transform>();

	switch (j)
	{
	case Direction::Right:
		if (m_IsOnGround)
		{
			m_Direction = MovementDirection::Right;
			movement.MoveHorizontally(deltaTime, horizontalSpeed, m_pTransform);		
		}
		break;
	case Direction::Left:
		if (m_IsOnGround)
		{
			movement.MoveHorizontally(deltaTime, -horizontalSpeed, m_pTransform);
			m_Direction = MovementDirection::Left;
		}
		break;
	case Direction::Up:
		if (m_IsOnLadder)
		{
			movement.MoveVertically(deltaTime, verticalSpeed, m_pTransform);
			m_Direction = MovementDirection::Up;
		}
		break;
	case Direction::Down:
		if (m_IsOnLadder)
		{
			movement.MoveVertically(deltaTime, -verticalSpeed, m_pTransform);
			m_Direction = MovementDirection::Down;
		}
		break;
	}

}
