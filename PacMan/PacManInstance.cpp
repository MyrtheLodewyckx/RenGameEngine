#include "PacManInstance.h"

#include "EventManager.h"
#include "Intermission.h"
#include "LevelManager.h"
#include "MainMenu.h"
#include "PacManEvents.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "ResultScene.h"


namespace dae
{
	class Scene;
}

void PacManInstance::Win()
{
	gGameState = state::win;
	int windowWidth{};
	int windowHeight{};
	SDL_GetWindowSize(dae::Renderer::GetInstance().get_window(), &windowWidth, &windowHeight);
	m_pBackGroundSprite->Resize(windowWidth, windowHeight);
	m_pBackGroundSprite->SetRowsCols(1, 2);
	++m_CurrentLevel;

	if(m_CurrentLevel == 4)
	{
		dae::InputManager::GetInstance().ClearCommands();
		auto scene = std::make_unique<Results>();
		dae::SceneManager::GetInstance().Add(std::move(scene), true);
		gGameState = state::neutral;
	}
}

void PacManInstance::SetMode(mode mode)
{
	m_GameMode = mode;
	std::cout << (int)m_GameMode;
}

mode PacManInstance::GetMode()
{
	return m_GameMode;
}

int PacManInstance::GetCurrentLevel()
{
	return m_CurrentLevel;
}

void PacManInstance::Initialize()
{
	auto pResourceManager = &dae::ResourceManager::GetInstance();
	auto font = pResourceManager->LoadFont("Fonts/pixel.otf", 30);
	m_pReadyTexture = pResourceManager->LoadTextureFromFont(font, "READY !", { 255,255,0 });
	m_pGameOverTexture = pResourceManager->LoadTextureFromFont(font, "GAME OVER", { 255,0,0 });

	m_pBackGroundSprite = m_GameObject->GetComponent<dae::SpriteComponent>();
}

void PacManInstance::Update(const float deltaTime)
{
	if(gGameState == state::win)
	{
		m_CurrentTime += deltaTime;
		const float maxTime{ 5.f };
		if (m_CurrentTime > maxTime)
		{
			m_CurrentTime = 0;
			dae::InputManager::GetInstance().ClearCommands();
			auto scene = std::make_unique<Intermission1>();
			dae::SceneManager::GetInstance().Add(std::move(scene), true);
			gGameState = state::neutral;
		}
	}

	if(gGameState == state::lose)
	{
		m_CurrentTime += deltaTime;
		const float maxTime{ 5.f };
		if (m_CurrentTime > maxTime)
		{
			m_CurrentTime = 0;
			m_CurrentLevel = 1;
			dae::InputManager::GetInstance().ClearCommands();
			auto scene = std::make_unique<MainMenu>();
			dae::SceneManager::GetInstance().Add(std::move(scene), true);
			gGameState = state::neutral;
		}
	}

	if (m_KeyboardRef->IsPressed(SDL_SCANCODE_F2))
	{
		++m_CurrentLevel;

		if (m_CurrentLevel == 4)
		{
			dae::InputManager::GetInstance().ClearCommands();
			auto scene = std::make_unique<Results>();
			dae::SceneManager::GetInstance().Add(std::move(scene), true);
			gGameState = state::neutral;
		}
		else
		{
			dae::InputManager::GetInstance().ClearCommands();
			auto scene = std::make_unique<Intermission1>();
			dae::SceneManager::GetInstance().Add(std::move(scene), true);
			gGameState = state::neutral;
		}


	}

	auto e = dae::EventManager::GetInstance().GetEvent();

	if (e == nullptr)
		return;

	switch (e->ID)
	{
	case (int)PacManEvents::WIN:
		Win();
		break;
	case (int)PacManEvents::LOSE:
		gGameState = state::lose;
		break;
	}


}

void PacManInstance::PostRender() const
{
	if (gGameState == state::lose)
	{
		int windowWidth{};
		SDL_GetWindowSize(m_pRendererRef->get_window(), &windowWidth, NULL);

		m_pRendererRef->RenderTexture(*m_pGameOverTexture, windowWidth * 0.5f - m_pGameOverTexture->GetSize().x * 0.5f, 415);
	}
}

void PacManInstance::SetBackGround(const dae::Sprite& pBackgroundSprite, int windowWidth, int windowHeight)
{
	m_pBackGroundSprite->SetSprite(pBackgroundSprite, windowWidth * 2.f, (float)windowHeight);
}
