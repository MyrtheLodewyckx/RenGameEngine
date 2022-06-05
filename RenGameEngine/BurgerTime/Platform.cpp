#include "pch.h"
#include "Platform.h"
#include "PlayerPhysics.h"
#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "TextureComponent.h"
#include "Enemy.h"
#include "Collision.h"
#include "AIPhysics.h"

std::vector<dae::Platform*> dae::Platform::m_ObjectList;

dae::Platform::Platform(GameObject* go)
    : Component(go)
{
    m_ObjectList.push_back(this);
}

dae::Platform::~Platform()
{
    auto newEnd = std::remove(m_ObjectList.begin(), m_ObjectList.end(), this);
    m_ObjectList.erase(newEnd, m_ObjectList.end());
}


void dae::Platform::HandlePlayerCollision()
{
    auto players = PlayerPhysics::GetAllInstances();

    for (int i = 0; i < (int)players.size(); ++i)
    {
        HandleOnePlayerCollision(players[i]);
    }
}

void dae::Platform::HandleEnemyCollision()
{
    auto enemies = AIPhysics::GetAllInstances();

    for (int i = 0; i < (int)enemies.size(); ++i)
    {
        for (int j = 0; j < (int)m_ObjectList.size(); ++j)
        {
            if (Collision::IsOverlapping(m_ObjectList[j]->m_HitBox, SDL_Rect(enemies[i]->GetHitBox().x, enemies[i]->GetHitBox().y + enemies[i]->GetHitBox().h - 1, enemies[i]->GetHitBox().w, 5)))
            {
                int PlatformId = (int)std::distance(m_ObjectList.begin(), std::find(m_ObjectList.begin(), m_ObjectList.end(), m_ObjectList[j]));
                enemies[i]->SetIsOnPlatform(PlatformId);

                return;
            }

            //make sure the player does not go out of bounds
            if (Collision::IsOverlapping(SDL_Rect(m_HitBox.x - 5, m_HitBox.y, m_HitBox.w + 10, m_HitBox.h), SDL_Rect(enemies[i]->GetHitBox().x, enemies[i]->GetHitBox().y + enemies[i]->GetHitBox().h, enemies[i]->GetHitBox().w, 2)))
            {
                if (enemies[i]->GetHitBox().x < m_HitBox.x)
                    enemies[i]->SetAiDirection(MovementDirection::Right);
                else if (enemies[i]->GetHitBox().x + enemies[i]->GetHitBox().w > m_HitBox.x + m_HitBox.w)
                    enemies[i]->SetAiDirection(MovementDirection::Left);
            }
        }
    }
}

void dae::Platform::HandleOnePlayerCollision(PlayerPhysics* player)
{
    for (int j = 0; j < (int)m_ObjectList.size(); ++j)
    {
        if (Collision::IsOverlapping(m_ObjectList[j]->m_HitBox, SDL_Rect(player->GetHitBox().x, player->GetHitBox().y + player->GetHitBox().h, player->GetHitBox().w, 1)))
        {
            player->m_IsOnGround = true;
            return;
        }

        //make sure the player does not go out of bounds
        if (Collision::IsOverlapping(SDL_Rect(m_HitBox.x - 5, m_HitBox.y, m_HitBox.w + 10, m_HitBox.h), SDL_Rect(player->GetHitBox().x, player->GetHitBox().y + player->GetHitBox().h, player->GetHitBox().w, 2)))
        {
            if (player->GetPos().x < m_HitBox.x)
                player->SetPos(glm::vec3(m_HitBox.x + 1, player->GetHitBox().y, 0));
            else if (player->GetPos().x + player->GetHitBox().w > m_HitBox.x + m_HitBox.w)
                player->SetPos(glm::vec3(m_HitBox.x + m_HitBox.w - 1 - player->GetHitBox().w, player->GetHitBox().y, 0));
        }
    }
    player->m_IsOnGround = false;
}

void dae::Platform::Update(const float)
{
    if (!m_texturePtr)
        m_texturePtr = m_Go->GetComponent<TextureComponent>();

    HandlePlayerCollision();
    HandleEnemyCollision();

}

void dae::Platform::Render() const
{
    Renderer::GetInstance().RenderTexture(*m_texturePtr->GetTexture().get(), (float)m_HitBox.x, (float)m_HitBox.y, (float)m_HitBox.w, (float)m_HitBox.h);
}

void dae::Platform::SetDimentions(int width, int height)
{
    m_HitBox.w = width;
    m_HitBox.h = height;

    m_HitBox.x = (int)m_Go->GetComponent<Transform>()->GetPosition().x;
    m_HitBox.y = (int)m_Go->GetComponent<Transform>()->GetPosition().y;
}


