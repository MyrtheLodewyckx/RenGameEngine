#include "MiniginPCH.h"
#include "Ladder.h"
#include "PlayerPhysics.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "utils.cpp"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "Enemy.h"
#include "Collision.h"

std::vector<dae::Ladder*> dae::Ladder::m_ObjectList;

dae::Ladder::Ladder(GameObject* go)
	:Component(go)
{
	m_ObjectList.push_back(this);
}

const void dae::Ladder::HandlePlayerCollision()
{
	auto players = PlayerPhysics::GetAllInstances();

	for (int i = 0; i < (int)players.size(); ++i)
	{
		for (int j = 0; j < (int)m_ObjectList.size(); ++j)
		{
			if (Collision::IsInRect(m_ObjectList[j]->m_HitBox, glm::vec3(players[i]->GetHitBox().x + players[i]->GetHitBox().w / 2.f, players[i]->GetHitBox().y + players[i]->GetHitBox().h, 0)))
			{
				players[i]->m_IsOnLadder = true;
				return;
			}

			//make sure the player does not go out of bounds
			if (Collision::IsInRect(SDL_Rect(m_HitBox.x, m_HitBox.y - 5, m_HitBox.w, m_HitBox.h + 10), glm::vec3(players[i]->GetHitBox().x + players[i]->GetHitBox().w / 2.f, players[i]->GetHitBox().y + players[i]->GetHitBox().h, 0)))
			{
				if (players[i]->GetPos().y + players[i]->GetHitBox().h > m_HitBox.y + m_HitBox.h)
					players[i]->SetPos(glm::vec3(players[i]->GetPos().x, m_HitBox.y + m_HitBox.h - players[i]->GetHitBox().h - 1, 0));
				else if (players[i]->GetPos().y + players[i]->GetHitBox().h < m_HitBox.y)
					players[i]->SetPos(glm::vec3(players[i]->GetPos().x, m_HitBox.y - players[i]->GetHitBox().h + 1, 0));
			}
		}
		players[i]->m_IsOnLadder = false;
	}
}

const void dae::Ladder::HandleEnemyCollision()
{
	auto enemies = Enemy::GetAllInstances();

	for (int i = 0; i < (int)enemies.size(); ++i)
	{
		for (int j = 0; j < (int)m_ObjectList.size(); ++j)
		{
			if (Collision::IsInRect(m_ObjectList[j]->m_HitBox, glm::vec2(enemies[i]->GetHitBox().x + enemies[i]->GetHitBox().w / 2.f, enemies[i]->GetHitBox().y + enemies[i]->GetHitBox().h)))
			{
				auto itr = std::find(m_ObjectList.begin(), m_ObjectList.end(), m_ObjectList[j]);
				int in = (int)std::distance(m_ObjectList.begin(), itr);
				enemies[i]->SetIsOverLadder(in);

				return;
			}

			//make sure the player does not go out of bounds
			if (Collision::IsInRect(SDL_Rect(m_HitBox.x, m_HitBox.y - 5, m_HitBox.w, m_HitBox.h + 10), glm::vec2(enemies[i]->GetHitBox().x + enemies[i]->GetHitBox().w / 2.f, enemies[i]->GetHitBox().y + enemies[i]->GetHitBox().h)))
			{
				if (enemies[i]->GetHitBox().y + enemies[i]->GetHitBox().h > m_HitBox.y + m_HitBox.h)
					enemies[i]->SetEnemyDirection(EnemyDirection::Down);
				else if (enemies[i]->GetHitBox().y + enemies[i]->GetHitBox().h < m_HitBox.y)
					enemies[i]->SetEnemyDirection(EnemyDirection::Up);
			}
		}
	}
}

void dae::Ladder::Update(const float)
{
	if (!m_texturePtr)
		m_texturePtr = m_Go->GetComponent<TextureComponent>();
	HandlePlayerCollision();

	HandleEnemyCollision();
	
}

void dae::Ladder::Render() const
{
	const float stepheight = m_texturePtr->GetTexture()->GetHeight();
	const int amtOfSteps = m_HitBox.h / (int)stepheight;
	
	for (int i = 1; i < amtOfSteps; ++i)
	{
		float yPos = float(m_HitBox.y + (i * stepheight));
		Renderer::GetInstance().RenderTexture(*m_texturePtr->GetTexture().get(), (float)m_HitBox.x, yPos,(float)m_HitBox.w, stepheight);
	}

	
}

void dae::Ladder::SetDimentions(int height, int width)
{
	m_HitBox.w = width;
	m_HitBox.h = height;

	m_HitBox.x = (int)m_Go->GetComponent<Transform>()->GetPosition().x;
	m_HitBox.y = (int)m_Go->GetComponent<Transform>()->GetPosition().y;
}


