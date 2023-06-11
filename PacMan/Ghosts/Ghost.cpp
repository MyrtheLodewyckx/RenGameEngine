#include "Ghost.h"

#include "EventManager.h"
#include "GameObject.h"
#include "GhostMovement.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "../PacManEvents.h"

void Ghost::SetSprites(dae::Sprite vertical, dae::Sprite sideways)
{
	m_SidewaysSprite = sideways;
	m_VerticalSprite = vertical;
}

void Ghost::SetDimentions(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

void Ghost::Initialize()
{
	m_pMovementRef = m_GameObject->GetComponent<Physics>();
	m_pSprite = m_GameObject->AddComponent<dae::SpriteComponent>();
	m_pSprite->SetSprite(m_SidewaysSprite, m_Width, m_Height);
	m_VulnerableSprite = dae::Sprite{ dae::ResourceManager::GetInstance().LoadTexture("Sprites/Ghosts/Vulnerable.png"),1,2,0.3f };
	m_VulnerableEndSprite = dae::Sprite{ dae::ResourceManager::GetInstance().LoadTexture("Sprites/Ghosts/Vulnerable_End.png"),1,2,0.3f };

	m_StartPos = m_GameObject->GetGlobalPos();
}

void Ghost::Update(const float deltaTime)
{

	if (m_IsVulnerable)
	{
		m_Timer += deltaTime;
		const float maxVulnerableTime{ 10.f };

		if (m_Timer >= maxVulnerableTime)
		{
			m_Timer = 0.f;
			m_IsVulnerable = false;
			m_ScoreValue = 200;
			m_pSprite->SetSprite(m_SidewaysSprite, m_Width, m_Height, SDL_FLIP_HORIZONTAL);
		}
		else if (m_Timer >= maxVulnerableTime - 3.f)
			m_pSprite->SetSprite(m_VulnerableEndSprite, m_Width, m_Height);
		return;
	}


	switch (m_pMovementRef->GetDirection())
	{
	case CONNECTS_UP:
		m_pSprite->SetSprite(m_VerticalSprite, m_Width, m_Height);
		break;
	case CONNECTS_DOWN:
		m_pSprite->SetSprite(m_VerticalSprite, m_Width, m_Height, SDL_FLIP_VERTICAL);
		break;
	case CONNECTS_LEFT:
		m_pSprite->SetSprite(m_SidewaysSprite, m_Width, m_Height, SDL_FLIP_HORIZONTAL);
		break;
	case CONNECTS_RIGHT:
		m_pSprite->SetSprite(m_SidewaysSprite, m_Width, m_Height);
		break;
	}



	auto e = dae::EventManager::GetInstance().GetEvent();
	if(e)
	{
		if(e->ID == (int)PacManEvents::POWER_PELLET_EAT)
		{
			m_IsVulnerable = true;
			m_pSprite->SetSprite(m_VulnerableSprite, m_Width, m_Height);
		}
	}
}

const bool Ghost::GetIsVulnerable()
{
	return m_IsVulnerable;
}

void Ghost::Eat()
{
	m_GameObject->SetPosition(m_StartPos);
	m_IsVulnerable = false;

	if (m_ScoreValue == 1600)
		m_ScoreValue = 200;
	else
	m_ScoreValue *= 2;

	m_pSprite->SetSprite(m_SidewaysSprite, m_Width, m_Height, SDL_FLIP_HORIZONTAL);
	m_IsFree = false;
}

const int Ghost::GetScoreValue()
{
	return m_ScoreValue;
}

const void Ghost::SetFree(bool isFree)
{
	m_IsFree = isFree;
}

bool Ghost::GetIsFree()
{
	return m_IsFree;
}
