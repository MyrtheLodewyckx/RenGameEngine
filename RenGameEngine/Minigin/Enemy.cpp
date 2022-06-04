#include "MiniginPCH.h"
#include "Enemy.h"
#include "Physics.h"
#include "ResourceManager.h"
#include "Player.h"
#include "Collision.h"
#include "Events.h"
#include "EventManager.h"

std::vector<Enemy*> Enemy::m_ObjectList{};

void Enemy::HandlePlayerCollision()
{
	if (m_ObjectList.empty())
		return;
	auto players = Player::GetAllInstances();
	auto hitbox = m_pPhysics->GetHitBox();

	for (auto player : players)
	{
		if (Collision::IsOverlapping(hitbox, SDL_Rect(player->GetHitBox())))
		{
			PlayerDiesEvent* e = new PlayerDiesEvent{};
			e->controllerIdx = player->GetPlayerIdx();
			dae::EventManager::GetInstance().AddEvent(e);
			m_ObjectList.clear();
			return;
		}
	}
}

void Enemy::HandleStun(const float deltaTime)
{
	auto hitbox = m_pPhysics->GetHitBox();
	m_pSprite->SetSprite(m_Sprites[3], (float)hitbox.w, (float)hitbox.h);

	float stunTime{ 5.f };
	m_Timer += deltaTime;

	if (m_Timer >= stunTime)
	{
		m_IsStunned = false;
		m_Timer = 0.f;
	}
}

void Enemy::HandleDeath(const float deltaTime)
{
	float deathTime{ 10.f };
	m_Timer += deltaTime;

	if (m_Timer >= deathTime)
	{
		m_IsDead = false;
		m_ObjectList.push_back(this);
		m_Timer = 0.f;
		m_pPhysics->SetPos(m_SpawnPoint);
		m_pSprite->m_IsRendering = true;
	}
}

void Enemy::Update(const float deltaTime)
{
	if (!m_pPhysics)
	{
		m_pPhysics = m_Go->GetComponent<Physics>();
		m_SpawnPoint = m_pPhysics->GetPos();
	}
	if (!m_pSprite)
		m_pSprite = m_Go->GetComponent<dae::SpriteComponent>();

	if (m_IsStunned)
		HandleStun(deltaTime);
	else if (m_IsDead)
		HandleDeath(deltaTime);
	else if(!m_IsFalling)
	{
		m_pPhysics->HandleMovement(deltaTime);
		//HandlePlayerCollision();
	}


	auto direction = m_pPhysics->GetDirection();
	auto hitbox = m_pPhysics->GetHitBox();

	switch (direction)
	{
	case MovementDirection::Left:
		m_pSprite->SetSprite(m_Sprites[2], (float)hitbox.w, (float)hitbox.h);
		break;
	case MovementDirection::Right:
		m_pSprite->SetSprite(m_Sprites[2], (float)hitbox.w, (float)hitbox.h, SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
		break;
	case MovementDirection::Down:
		m_pSprite->SetSprite(m_Sprites[1], (float)hitbox.w, (float)hitbox.h);
		break;
	case MovementDirection::Up:
		m_pSprite->SetSprite(m_Sprites[0], (float)hitbox.w, (float)hitbox.h);
		break;
	}
}

void Enemy::SetEnemyID(EnemyID id)
{
	auto& resourceManager = dae::ResourceManager::GetInstance();

	switch (id)
	{
	case EnemyID::Sausage:
		m_Sprites[0] = dae::Sprite(resourceManager.LoadTexture("sprites/SausageWalkingForward.png"),1,2,0.25f);
		m_Sprites[1] = dae::Sprite(resourceManager.LoadTexture("sprites/SausageClimbingUp.png"),1,2,0.25f);
		m_Sprites[2] = dae::Sprite(resourceManager.LoadTexture("sprites/SausageWalking.png"), 1, 2, 0.25f);
		m_Sprites[3] = dae::Sprite(resourceManager.LoadTexture("sprites/SausageStunned.png"), 1, 2, 0.25f);
		break;
	case EnemyID::Egg:
		m_Sprites[0] = dae::Sprite(resourceManager.LoadTexture("sprites/EggWalkingForward.png"), 1, 2, 0.25f);
		m_Sprites[1] = dae::Sprite(resourceManager.LoadTexture("sprites/EggClimbingUp.png"), 1, 2, 0.25f);
		m_Sprites[2] = dae::Sprite(resourceManager.LoadTexture("sprites/EggWalking.png"), 1, 2, 0.25f);
		m_Sprites[3] = dae::Sprite(resourceManager.LoadTexture("sprites/EggStunned.png"), 1, 2, 0.25f);
		break;
	case EnemyID::Pickle:
		m_Sprites[0] = dae::Sprite(resourceManager.LoadTexture("sprites/PickleWalkingForward.png"), 1, 2, 0.25f);
		m_Sprites[1] = dae::Sprite(resourceManager.LoadTexture("sprites/PickleClimbingUp.png"), 1, 2, 0.25f);
		m_Sprites[2] = dae::Sprite(resourceManager.LoadTexture("sprites/PickleWalking.png"), 1, 2, 0.25f);
		m_Sprites[3] = dae::Sprite(resourceManager.LoadTexture("sprites/PickleStunned.png"), 1, 2, 0.25f);
		break;
	}

	m_ID = id;
}

void Enemy::Die()
{
	auto newEnd = std::remove(m_ObjectList.begin(), m_ObjectList.end(), this);
	m_ObjectList.erase(newEnd, m_ObjectList.end());
	m_IsDead = true;
	m_IsStunned = false;
	m_IsFalling = false;
	m_pSprite->m_IsRendering = false;
	m_Timer = 0;

	ScoreChangeEvent* e = new ScoreChangeEvent();
	e->amt = 100 + int(m_ID) * 100;
	dae::EventManager::GetInstance().AddEvent(e);
}

Enemy::~Enemy()
{
	auto newEnd = std::remove(m_ObjectList.begin(), m_ObjectList.end(), this);
	m_ObjectList.erase(newEnd, m_ObjectList.end());
}
