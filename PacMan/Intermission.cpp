#include "Intermission.h"

#include "LevelManager.h"
#include "PacManInstance.h"
#include "PacManSounds.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "SoundSystem.h"
#include "SpriteComponent.h"

void Intermission1::Update(const float deltaTime )
{
	Scene::Update(deltaTime);
	float fleeSpeed{(m_WindWidth + 40.f)/5.f};
	float chaseSpeed{ (m_WindWidth + 70.f)/5.f };
	m_Timer += deltaTime;

	auto pacPos = m_PacMan->GetGlobalPos();
	auto blinkyPos = m_Ghost->GetGlobalPos();

	if(m_Timer < 6.f)
	{
		m_PacMan->SetPosition(pacPos.x - fleeSpeed * deltaTime, pacPos.y,pacPos.z);
		m_Ghost->SetPosition(blinkyPos.x - chaseSpeed * deltaTime, blinkyPos.y, blinkyPos.z);
	}
	else if(m_Timer < 12.f)
	{
		if(!m_IsHalfway)
		{
			m_IsHalfway = true;
			m_PacMan->GetComponent<dae::SpriteComponent>()->SetSprite(
				dae::Sprite{ dae::ResourceManager::GetInstance().LoadTexture("Sprites/PacMan_Sideways.png"),
				1,3,0.1f }, 50, 50);
			pacPos.x = -100;
			pacPos.y -= 15.f;

			m_Ghost->GetComponent<dae::SpriteComponent>()->SetSprite(
				dae::Sprite{ dae::ResourceManager::GetInstance().LoadTexture("Sprites/Ghosts/Vulnerable.png"),
				1,2,0.1f }, 20, 20);
			blinkyPos.x = -20;
			sound_system* a = &AudioServiceLocator::get_sound_system();
			a->Play((int)PacManSounds::INTERMISSION, 50);
		}
		m_PacMan->SetPosition(pacPos.x + chaseSpeed * deltaTime, pacPos.y, pacPos.z);
		m_Ghost->SetPosition(blinkyPos.x + fleeSpeed * deltaTime, blinkyPos.y, blinkyPos.z);
	}
	else
	{
		auto scene = std::make_unique<dae::Scene>("Level " + std::to_string(PacManInstance::GetCurrentLevel()));
		dae::LevelManager::GetInstance().LoadLevel(PacManInstance::GetCurrentLevel(), *scene);
		dae::SceneManager::GetInstance().Add(std::move(scene), true);
		gGameState = state::neutral;
	}
}

void Intermission1::Initialize()
{
	SDL_GetWindowSize(dae::Renderer::GetInstance().get_window(), &m_WindWidth, &m_WindHeight);

	m_PacMan = std::make_shared<dae::GameObject>();
	dae::Sprite sprite = { dae::ResourceManager::GetInstance().LoadTexture("Sprites/PacMan_Sideways.png"),1,3,0.1f };

	m_PacMan->AddComponent<dae::SpriteComponent>()->SetSprite(sprite,20.f,20.f,SDL_FLIP_HORIZONTAL);
	m_PacMan->SetPosition((float)m_WindWidth, (float)m_WindHeight / 2.f, 0);


	m_Ghost = std::make_shared<dae::GameObject>();
	sprite = { dae::ResourceManager::GetInstance().LoadTexture("Sprites/Ghosts/Blinky_Sideways.png"),1,2,0.3f };
	m_Ghost->AddComponent<dae::SpriteComponent>()->SetSprite(sprite, 20.f, 20.f, SDL_FLIP_HORIZONTAL);
	m_Ghost->SetPosition((float)m_WindWidth + 50.f, (float)m_WindHeight / 2.f, 0);
	Add(m_Ghost);
	Add(m_PacMan);


	sound_system* a = &AudioServiceLocator::get_sound_system();
	a->Play((int)PacManSounds::INTERMISSION, 50);
}
