#include "MiniginPCH.h"
#include "Enemy.h"
#include "PlayerPhysics.h"
#include "GameObject.h"
#include <algorithm>
#include "movement.h"
#include "ResourceManager.h"
#include "PlayerPhysics.h"
#include "Collision.h"
#include "EventManager.h"

std::vector<dae::Enemy*> dae::Enemy::m_ObjectList;

void dae::Enemy::HandleMovement(const float deltaTime)
{
	Movement move{};
	const int horizontalSpeed{ 50 };	
	const int verticalSpeed{ 30 };

	switch (m_Direction)
	{
	case EnemyDirection::Left:
		move.MoveHorizontally(deltaTime, -horizontalSpeed, m_pTransform);
		m_pSprite->SetSprite(m_Sprites[1], (float)m_Width, (float)m_Height);
		break;
	case EnemyDirection::Right:
		move.MoveHorizontally(deltaTime, horizontalSpeed, m_pTransform);
		m_pSprite->SetSprite(m_Sprites[1], (float)m_Width, (float)m_Height, SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
		break;
	case EnemyDirection::Up:
		move.MoveVertically(deltaTime, -verticalSpeed, m_pTransform);
		m_pSprite->SetSprite(m_Sprites[0], (float)m_Width, (float)m_Height);
		break;
	case EnemyDirection::Down:
		move.MoveVertically(deltaTime, verticalSpeed, m_pTransform);
		m_pSprite->SetSprite(m_Sprites[2], (float)m_Width, (float)m_Height);
		break;
	}

}

void dae::Enemy::HandlePlayerCollision()
{
	if (m_ObjectList.empty())
		return;
	auto players = PlayerPhysics::GetAllInstances();

	for (auto player : players)
	{
		if (Collision::IsOverlapping(SDL_Rect((int)m_pTransform->GetPosition().x, (int)m_pTransform->GetPosition().y, m_Width, m_Height), SDL_Rect(player->GetHitBox())))
		{
			PlayerDiesEvent* e = new PlayerDiesEvent{};
			e->controllerIdx = player->GetControllerIdx();
			dae::EventManager::GetInstance().AddEvent(e);
			m_ObjectList.clear();
			return;
		}
	}
}

void dae::Enemy::HandleStun(const float deltaTime)
{
	m_pSprite->SetSprite(m_Sprites[3], (float)m_Width, (float)m_Height);

	float stunTime{ 5.f };
	m_Timer += deltaTime;

	if (m_Timer >= stunTime)
	{
		m_IsStunned = false;
		m_Timer = 0.f;
	}
}

void dae::Enemy::SetIsStunned(bool b)
{
	m_IsStunned = b;
}

SDL_Rect dae::Enemy::GetHitBox()
{
	if (!m_pTransform)
		m_pTransform = m_Go->GetComponent<Transform>();
	return SDL_Rect((int)m_pTransform->GetPosition().x, (int)m_pTransform->GetPosition().y, m_Width, m_Height);
}

void dae::Enemy::SetPos(glm::vec3 pos)
{
	m_pTransform->SetPosition(pos);
}

std::vector<dae::Enemy*> dae::Enemy::GetAllInstances()
{
	return m_ObjectList;
}

void dae::Enemy::SetValues(EnemyID id, int height, int width)
{
	auto& resourceManager = dae::ResourceManager::GetInstance();

	switch (id)
	{
	case EnemyID::MrHotDog:
		m_pClimbingDownTexture = resourceManager.LoadTexture("sprites/SausageWalkingForward.png");
		m_pClimbingUpTexture = resourceManager.LoadTexture("sprites/SausageClimbingUp.png");
		m_pWalkingTexture = resourceManager.LoadTexture("sprites/SausageWalking.png");
		m_pStunnedTexture = resourceManager.LoadTexture("sprites/SausageStunned.png");
		break;
	case EnemyID::MrEgg:
		m_pClimbingDownTexture = resourceManager.LoadTexture("sprites/EggWalkingForward.png");
		m_pClimbingUpTexture = resourceManager.LoadTexture("sprites/EggClimbingUp.png");
		m_pWalkingTexture = resourceManager.LoadTexture("sprites/EggWalking.png");
		m_pStunnedTexture = resourceManager.LoadTexture("sprites/EggStunned.png");
		break;
	case EnemyID::MrPickle:
		m_pClimbingDownTexture = resourceManager.LoadTexture("sprites/PickleWalkingForward.png");
		m_pClimbingUpTexture = resourceManager.LoadTexture("sprites/PickleClimbingUp.png");
		m_pWalkingTexture = resourceManager.LoadTexture("sprites/PickleWalking.png");
		m_pStunnedTexture = resourceManager.LoadTexture("sprites/EggStunned.png");
		break;
	}

	m_Sprites[0].texturePtr = m_pClimbingDownTexture;
	m_Sprites[1].texturePtr = m_pWalkingTexture;
	m_Sprites[2].texturePtr = m_pClimbingUpTexture;
	m_Sprites[3].texturePtr = m_pStunnedTexture;

	m_Height = height;
	m_Width = width;
}

dae::Enemy::Enemy(GameObject* go)
	:Component(go)
{
	m_ObjectList.emplace_back(this);
}

dae::Enemy::~Enemy()
{
	auto newEnd = std::remove(m_ObjectList.begin(), m_ObjectList.end(), this);
	m_ObjectList.erase(newEnd, m_ObjectList.end());
}
 
void dae::Enemy::Update(const float deltaTime)
{
	if (!m_pTransform)
		m_pTransform = m_Go->GetComponent<Transform>();

	if(!m_pSprite)
		m_pSprite = m_Go->GetComponent<SpriteComponent>();

	if (m_IsStunned)
		HandleStun(deltaTime);
	else
	{
		HandleMovement(deltaTime);
		HandlePlayerCollision();
	}
}

void dae::Enemy::SetIsOverLadder(int ladderIndex)
{
	if (ladderIndex != m_LadderIdx)
	{
		m_LadderIdx = ladderIndex;

		//GET CLOSEST PLAYER
		auto players = PlayerPhysics::GetAllInstances();
		auto currentpos = m_pTransform->GetPosition();
		auto compareDistance = [currentpos](PlayerPhysics* p1, PlayerPhysics* p2) -> bool { return(glm::distance(currentpos, p1->GetPos()) < glm::distance(currentpos, p2->GetPos())); };

		auto closestPlayerItr = std::max_element(players.begin(), players.end(), compareDistance);

		if (players[(int)std::distance(players.begin(), closestPlayerItr)]->GetPos().y > m_pTransform->GetPosition().y)
			m_Direction = EnemyDirection::Up;
		else m_Direction = EnemyDirection::Down;
	}
}

void dae::Enemy::SetIsOnPlatform(int platformIndex)
{
	if (platformIndex != m_PlatformIdx && m_Direction!= EnemyDirection::Left && m_Direction != EnemyDirection::Right)
	{
		m_PlatformIdx = platformIndex;

		//GET CLOSEST PLAYER
		auto players = PlayerPhysics::GetAllInstances();
		auto currentpos = m_pTransform->GetPosition();
		auto compareDistance = [currentpos](PlayerPhysics* p1, PlayerPhysics* p2) -> bool { return(glm::distance(currentpos, p1->GetPos()) < glm::distance(currentpos, p2->GetPos())); };

		auto closestPlayerItr = std::max_element(players.begin(), players.end(), compareDistance);

		if (players[(int)std::distance(players.begin(), closestPlayerItr)]->GetPos().x > m_pTransform->GetPosition().x)
			m_Direction = EnemyDirection::Right;
		else m_Direction = EnemyDirection::Left;
	}
}

void dae::Enemy::SetEnemyDirection(EnemyDirection direction)
{
	m_Direction = direction;
}
