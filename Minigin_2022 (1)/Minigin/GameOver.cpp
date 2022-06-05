#include "MiniginPCH.h"
#include "GameOver.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameStateManager.h"
#include "Scene.h"
#include "LevelManager.h"
#include "GameStateManager.h"
#include "Options.h"


void GameOver::ControllerUpdate()
{
	if (m_InputManagerRef.IsPressed(dae::ControllerButton::ButtonA, 0))
	{
		switch (m_ActiveButtonId)
		{
		case GameOverButtons::PLAY:
		{
			auto scene = std::make_unique<dae::Scene>(1);
			dae::LevelManager::GetInstance().LoadLevel("lvl1.txt", *scene.get());
			dae::GameStateManager::GetInstance().Add(std::move(scene), 1);
		}
		break;
		case GameOverButtons::QUIT:
		{
			auto options = std::make_unique<Options>();
			dae::GameStateManager::GetInstance().Add(std::move(options));
		}
		break;
		}
	}
}

void GameOver::KeyboardUpdate()
{
	if (m_InputManagerRef.IsPressed(SDL_SCANCODE_RETURN))
	{
		switch (m_ActiveButtonId)
		{
		case GameOverButtons::PLAY:
		{
			auto scene = std::make_unique<dae::Scene>(1);
			dae::LevelManager::GetInstance().LoadLevel("lvl1.txt", *scene.get());
			dae::GameStateManager::GetInstance().Add(std::move(scene), 1);
		}
		break;
		case GameOverButtons::QUIT:
		{
			m_InputManagerRef.m_IsClosingProgram = true;
		}
		break;
		}
	}
}

GameOver::GameOver()
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{

	m_pPeterHeadIcon = dae::ResourceManager::GetInstance().LoadTexture("PeterHead.png");
	auto font = dae::ResourceManager::GetInstance().LoadFont("pixel.otf", 20);
	m_pReplayButtonTexture = dae::ResourceManager::GetInstance().LoadTextureFromFont(font, "REPLAY");
	m_pQuitButtonTexture = dae::ResourceManager::GetInstance().LoadTextureFromFont(font, "QUIT");
	m_pVictoryTexture = dae::ResourceManager::GetInstance().LoadTextureFromFont(font, "GAME OVER");
}

void GameOver::HandleInput()
{
	auto j = dae::InputManager::GetInstance().GetMenuDirection(0);

	if (j == dae::Direction::Up)
		m_ActiveButtonId = GameOverButtons(((unsigned int)m_ActiveButtonId - 1) % (int)GameOverButtons::COUNT);
	if (j == dae::Direction::Down)
		m_ActiveButtonId = GameOverButtons(((unsigned int)m_ActiveButtonId + 1) % (int)GameOverButtons::COUNT);
}

void GameOver::Update(const float)
{
	auto inDevice = m_InputManagerRef.GetInputDevice(0);
	if (inDevice == dae::InputDevices::KeyBoard)
		KeyboardUpdate();
	else if (inDevice == dae::InputDevices::XBoxController)
		ControllerUpdate();
}

void GameOver::Render() const
{


	auto& renderer = dae::Renderer::GetInstance();

	int windowWidth{ 0 };
	int windowHeight{ 0 };
	SDL_GetWindowSize(renderer.GetWindow(), &windowWidth, &windowHeight);


	glm::vec2 logoPos{ windowWidth / 2 - m_pVictoryTexture->GetWidth() / 2 ,20 + m_pVictoryTexture->GetHeight() };
	glm::vec2 playButtonPos{ windowWidth / 2 - m_pReplayButtonTexture->GetWidth() / 2 ,logoPos.y + m_pVictoryTexture->GetHeight() + 40 + m_pReplayButtonTexture->GetHeight() };
	glm::vec2 optionsButtonPos{ windowWidth / 2 - m_pQuitButtonTexture->GetWidth() / 2, playButtonPos.y + 20 + m_pQuitButtonTexture->GetHeight() };

	renderer.RenderTexture(*m_pVictoryTexture.get(), logoPos.x, logoPos.y);
	renderer.RenderTexture(*m_pReplayButtonTexture.get(), playButtonPos.x, playButtonPos.y);
	renderer.RenderTexture(*m_pQuitButtonTexture.get(), optionsButtonPos.x, optionsButtonPos.y);

	glm::vec2 iconPos{};
	int iconspacer{ 10 };
	int iconSizeMultiplier{ 2 };


	switch (m_ActiveButtonId)
	{
	case GameOverButtons::QUIT:
		iconPos.x = optionsButtonPos.x - iconspacer - m_pPeterHeadIcon->GetWidth() * iconSizeMultiplier;
		iconPos.y = optionsButtonPos.y + m_pQuitButtonTexture->GetHeight() / 2 - m_pPeterHeadIcon->GetHeight() / 2;
		break;
	case GameOverButtons::PLAY:
		iconPos.x = playButtonPos.x - iconspacer - m_pPeterHeadIcon->GetWidth() * iconSizeMultiplier;
		iconPos.y = playButtonPos.y + m_pReplayButtonTexture->GetHeight() / 2 - m_pPeterHeadIcon->GetHeight() / 2;
		break;
	default:
		std::cerr << "Not all button positions are included.";
	}

	renderer.RenderTexture(*m_pPeterHeadIcon.get(), iconPos.x, iconPos.y, m_pPeterHeadIcon->GetWidth() * iconSizeMultiplier, m_pPeterHeadIcon->GetHeight() * iconSizeMultiplier);
}