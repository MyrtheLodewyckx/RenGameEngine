#include <SceneManager.h>
#include "PacMan.h"

#include "Controller.h"
#include "EventManager.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Pellet.h"
#include "PlayerPhysicsComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SpriteComponent.h"
#include "GeometryUtils.h"
#include "PacManEvents.h"
#include "PacManSounds.h"
#include "SoundSystem.h"
#include "Ghosts/Ghost.h"

void PacMan::Initialize()
{
	m_pSprite = m_GameObject->GetComponent<dae::SpriteComponent>();
	m_pPhysicsRef = m_GameObject->GetComponent<PlayerPhysicsComponent>();

	m_PelletsRef = dae::SceneManager::GetInstance().GetCurrentScene()->GetAllGameObjectsWithComponent<Pellet>();
	m_GhostsRef = dae::SceneManager::GetInstance().GetCurrentScene()->GetAllGameObjectsWithComponent<Ghost>();

	m_StartPos = m_GameObject->GetGlobalPos();
	m_PelletsEaten = 0;

}

int PacMan::GetPelletsEaten()
{
	return m_PelletsEaten;
}

void PacMan::CheckForPellets()
{
	
	for(int i{0}; i < (int)m_PelletsRef.size(); ++i)
	{
		auto pelletPos = m_PelletsRef[i]->GetGlobalPos();
		auto pacPos = m_GameObject->GetGlobalPos();
		auto w = m_pSprite->GetWidth();
		auto h = m_pSprite->GetHeight();
		if (m_PelletsRef[i] && GeoUtils::IsPointInRect(glm::vec2{pelletPos.x,pelletPos.y}, SDL_Rect{(int)pacPos.x,(int)pacPos.y,(int)w,(int)h}))
		{
			auto scoreEvent = new SCORE_CHANGE();
			scoreEvent->amt = m_PelletsRef[i]->GetComponent<Pellet>()->m_Amt;
			if(scoreEvent->amt == 50)
			{
				sound_system* a = &AudioServiceLocator::get_sound_system();
				a->Play((int)PacManSounds::POWER_PELLET, 50);

				auto powerEvent = new POWER_PELLET_EAT();
				dae::EventManager::GetInstance().AddEvent(powerEvent);
			}

			dae::EventManager::GetInstance().AddEvent(scoreEvent);
			m_PelletsRef[i]->remove();
			++m_PelletsEaten;
			m_PelletsRef.erase(std::remove(m_PelletsRef.begin(), m_PelletsRef.end(), m_PelletsRef[i]), m_PelletsRef.end());
			{
				sound_system* a = &AudioServiceLocator::get_sound_system();
				a->Play((int)PacManSounds::MUNCH_1 + m_MunchSound, 50);
				m_MunchSound = !m_MunchSound;
				if(m_PelletsRef.empty())
				{
					auto WinEvent = new WIN();
					dae::EventManager::GetInstance().AddEvent(WinEvent);
				}

			}
		}
	}
}

void PacMan::CheckForGhosts()
{
	for (int i{ 0 }; i < (int)m_GhostsRef.size(); ++i)
	{
		auto GhostPos = m_GhostsRef[i]->GetGlobalPos();
		auto pacPos = m_GameObject->GetGlobalPos();
		auto w = m_pSprite->GetWidth();
		auto h = m_pSprite->GetHeight();
		if (m_GhostsRef[i] && GeoUtils::IsPointInRect(glm::vec2{ GhostPos.x,GhostPos.y }, SDL_Rect{ (int)pacPos.x,(int)pacPos.y,(int)w,(int)h }))
		{
			auto ghost = m_GhostsRef[i]->GetComponent<Ghost>();
			if(ghost->GetIsVulnerable())
			{
				sound_system* a = &AudioServiceLocator::get_sound_system();
				a->Play((int)PacManSounds::EAT_GHOST, 50);
				ghost->Eat();
				auto scoreEvent = new SCORE_CHANGE();
				scoreEvent->amt = ghost->GetScoreValue();
				dae::EventManager::GetInstance().AddEvent(scoreEvent);
			}
			else
			{
				m_pPhysicsRef->SetIsDying(true);
				m_pSprite->SetSprite(m_DyingSprite, m_Width, m_Height);
				m_pSprite->Reset();
				sound_system* a = &AudioServiceLocator::get_sound_system();
				a->Play((int)PacManSounds::PLAYER_DIES, 50);

				auto livesEvent = new LIVES_CHANGE();
				livesEvent->amt = -1;
				dae::EventManager::GetInstance().AddEvent(livesEvent);
			}
		}
	}
}

PacMan::~PacMan()
{}

void PacMan::SetDimentions(int width, int height)
{
	m_Width = (float)width;
	m_Height = (float)height;

	if(m_pSprite)
	m_pSprite->Resize(width, height);
}

void PacMan::SetSprites(dae::Sprite sideWays, dae::Sprite vertical, dae::Sprite dying)
{
	m_SidewaysSprite = sideWays;
	m_VerticalSprite = vertical;
	m_DyingSprite = dying;
}

void PacMan::Update(const float deltaTime)
{
	if(m_pPhysicsRef->GetIsDying())
	{
		m_Timer += deltaTime;
		float maxTime = m_pSprite->GetSpriteTime();
		if (m_Timer > maxTime)
		{
			m_Timer = 0;
			m_GameObject->SetPosition(m_StartPos);
			m_pPhysicsRef->SetIsDying(false);
		}

		return;
	}

	CheckForPellets();

	switch(m_pPhysicsRef->GetDirection())
	{
	case CONNECTS_UP:
		m_pSprite->SetSprite(m_VerticalSprite, m_Width, m_Height);
		break;
	case CONNECTS_DOWN:
		m_pSprite->SetSprite(m_VerticalSprite, m_Width, m_Height,SDL_FLIP_VERTICAL);
		break;
	case CONNECTS_LEFT:
		m_pSprite->SetSprite(m_SidewaysSprite, m_Width, m_Height, SDL_FLIP_HORIZONTAL);
		break;
	case CONNECTS_RIGHT:
		m_pSprite->SetSprite(m_SidewaysSprite, m_Width, m_Height);
		break;
	}

	CheckForGhosts();
}


