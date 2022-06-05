#include "pch.h"
#include "AIPhysics.h"
#include "PlayerPhysics.h"
#include "GameObject.h"
#include <algorithm>
#include "movement.h"
#include "ResourceManager.h"
#include "PlayerPhysics.h"
#include "Collision.h"
#include "EventManager.h"

std::vector<AIPhysics*> AIPhysics::m_ObjectList;

void AIPhysics::HandleMovement(const float deltaTime)
{
	dae::Movement move{};
	const int horizontalSpeed{ 50 };	
	const int verticalSpeed{ 30 };

	switch (m_Direction)
	{
	case MovementDirection::Left:
		move.MoveHorizontally(deltaTime, -horizontalSpeed, m_pTransform);
		break;
	case MovementDirection::Right:
		move.MoveHorizontally(deltaTime, horizontalSpeed, m_pTransform);
		break;
	case MovementDirection::Up:
		move.MoveVertically(deltaTime, -verticalSpeed, m_pTransform);
		break;
	case MovementDirection::Down:
		move.MoveVertically(deltaTime, verticalSpeed, m_pTransform);
		break;
	}

}

SDL_Rect AIPhysics::GetHitBox()
{
	if (!m_pTransform)
		m_pTransform = m_Go->GetComponent<dae::Transform>();
	return SDL_Rect(m_pTransform->GetHitBox());
}

void AIPhysics::SetPos(glm::vec3 pos)
{
	m_pTransform->SetPosition(pos);
}

std::vector<AIPhysics*> AIPhysics::GetAllInstances()
{
	return m_ObjectList;
}

AIPhysics::AIPhysics(dae::GameObject* go)
	:Physics(go)
{
	m_ObjectList.emplace_back(this);
}

AIPhysics::~AIPhysics()
{
	auto newEnd = std::remove(m_ObjectList.begin(), m_ObjectList.end(), this);
	m_ObjectList.erase(newEnd, m_ObjectList.end());
}
 
void AIPhysics::Update(const float)
{
	if (!m_pTransform)
		m_pTransform = m_Go->GetComponent<dae::Transform>();
}

void AIPhysics::SetIsOverLadder(int ladderIndex)
{
	if (ladderIndex != m_LadderIdx)
	{
		m_LadderIdx = ladderIndex;

		//GET CLOSEST PLAYER
		auto players = dae::PlayerPhysics::GetAllInstances();
		auto currentpos = m_pTransform->GetPosition();
		auto compareDistance = [currentpos](dae::PlayerPhysics* p1, dae::PlayerPhysics* p2) -> bool { return(glm::distance(currentpos, p1->GetPos()) < glm::distance(currentpos, p2->GetPos())); };

		auto closestPlayerItr = std::max_element(players.begin(), players.end(), compareDistance);

		if (players[(int)std::distance(players.begin(), closestPlayerItr)]->GetPos().y > m_pTransform->GetPosition().y)
			m_Direction = MovementDirection::Up;
		else m_Direction = MovementDirection::Down;
	}
}

void AIPhysics::SetIsOnPlatform(int platformIndex)
{
	if (platformIndex != m_PlatformIdx && m_Direction!= MovementDirection::Left && m_Direction != MovementDirection::Right)
	{
		m_PlatformIdx = platformIndex;

		//GET CLOSEST PLAYER
		auto players = dae::PlayerPhysics::GetAllInstances();
		auto currentpos = m_pTransform->GetPosition();
		auto compareDistance = [currentpos](dae::PlayerPhysics* p1, dae::PlayerPhysics* p2) -> bool { return(glm::distance(currentpos, p1->GetPos()) < glm::distance(currentpos, p2->GetPos())); };

		auto closestPlayerItr = std::max_element(players.begin(), players.end(), compareDistance);

		if (players[(int)std::distance(players.begin(), closestPlayerItr)]->GetPos().x > m_pTransform->GetPosition().x)
			m_Direction = MovementDirection::Right;
		else m_Direction = MovementDirection::Left;
	}
}

void AIPhysics::SetAiDirection(MovementDirection direction)
{
	m_Direction = direction;
}
