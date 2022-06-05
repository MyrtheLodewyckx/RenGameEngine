#include "MiniginPCH.h"
#include "Player.h"
#include "Enemy.h"
#include "Collision.h"
#include "ResourceManager.h"
#include "Physics.h"

std::vector<Player*> Player::m_ObjectList{};

void Player::SetPlayerIdx(int idx)
{
	m_PlayerIdx = idx;

	std::string str;

	str = "sprites/Player" + std::to_string(++idx) + "WalkingSideways.png";
	m_Sprites[0] = dae::Sprite(dae::ResourceManager::GetInstance().LoadTexture(str),1,3,0.5f);
	str = "sprites/Player" + std::to_string(idx) + "WalkingForward.png";
	m_Sprites[1] = dae::Sprite(dae::ResourceManager::GetInstance().LoadTexture(str), 1, 3, 0.5f);
	str = "sprites/Player" + std::to_string(idx) + "ClimbingUp.png";
	m_Sprites[2] = dae::Sprite(dae::ResourceManager::GetInstance().LoadTexture(str), 1, 3, 0.5f);
}

void Player::ThrowPepper()
{
		if (m_PepperCharges > 0)
		{
			--m_PepperCharges;
			auto enemies = Enemy::GetAllInstances();

			auto hitbox = m_pPhysics->GetHitBox();

			for (Enemy* enemy : enemies)
			{
				if (m_pPhysics->GetDirection() == MovementDirection::Left && Collision::IsOverlapping(enemy->GetHitBox(), SDL_Rect(hitbox.x - hitbox.w, hitbox.y, hitbox.w, hitbox.h)))
					enemy->SetIsStunned(true);
				else if (m_pPhysics->GetDirection() != MovementDirection::Left && Collision::IsOverlapping(enemy->GetHitBox(), SDL_Rect(hitbox.x + hitbox.w * 2, hitbox.y, hitbox.w, hitbox.h)))
					enemy->SetIsStunned(true);
			}
		}
}

Player::~Player()
{
	auto newEnd = std::remove(m_ObjectList.begin(), m_ObjectList.end(), this);
	m_ObjectList.erase(newEnd, m_ObjectList.end());
}

void Player::Update(const float deltaTime)
{
	auto direction = m_pPhysics->GetDirection();
	auto hitbox = m_pPhysics->GetHitBox();

	m_pPhysics->HandleMovement(deltaTime);

		switch (direction)
		{
			case MovementDirection::Left:
				m_pSprite->SetSprite(m_Sprites[0], (float)hitbox.w, (float)hitbox.h);
				break;
			case MovementDirection::Right:
				m_pSprite->SetSprite(m_Sprites[0], (float)hitbox.w, (float)hitbox.h,SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
				break;
			case MovementDirection::Down:
				m_pSprite->SetSprite(m_Sprites[1], (float)hitbox.w, (float)hitbox.h);
				break;
			case MovementDirection::Up:
				m_pSprite->SetSprite(m_Sprites[2], (float)hitbox.w, (float)hitbox.h);
				break;
		}
}
