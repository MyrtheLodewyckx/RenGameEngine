#include "MiniginPCH.h"
#include "MainMenu.h"
#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_sdl.h"
#include "Imgui/imgui_impl_opengl2.h"
#include "Imgui/imgui_plot.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "InputManager.h"
#include "GameStateManager.h"
#include "Scene.h"
#include "LevelManager.h"
#include "GameStateManager.h"
#include "Options.h"


MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
	m_pLogoTexture = dae::ResourceManager::GetInstance().LoadTexture("BurgerTimeLogo.png");
	m_pPeterHeadIcon = dae::ResourceManager::GetInstance().LoadTexture("PeterHead.png");
	auto font = dae::ResourceManager::GetInstance().LoadFont("pixel.otf", 20);
	m_pOptionsButtonTexture = dae::ResourceManager::GetInstance().LoadTextureFromFont(font, "OPTIONS");
	m_pPlayButtonTexture = dae::ResourceManager::GetInstance().LoadTextureFromFont(font, "PLAY");
}

void MainMenu::HandleInput()
{
	auto j = dae::InputManager::GetInstance().GetJoystickDirection(0);

	if (j == dae::Direction::Up || dae::InputManager::GetInstance().IsPressed(dae::ControllerButton::DPAD_UP, 0))
		m_ActiveButtonId = MainMenuButtons(((unsigned int)m_ActiveButtonId - 1)%(int)MainMenuButtons::COUNT);
	if (j == dae::Direction::Down || dae::InputManager::GetInstance().IsPressed(dae::ControllerButton::DPAD_DOWN, 0))
		m_ActiveButtonId = MainMenuButtons(((unsigned int)m_ActiveButtonId + 1)%(int)MainMenuButtons::COUNT);
}

void MainMenu::Update(const float)
{
	if (dae::InputManager::GetInstance().IsPressed(dae::ControllerButton::ButtonA, 0))
	{
		switch (m_ActiveButtonId)
		{
		case MainMenuButtons::PLAY:
		{
			auto scene = std::make_unique<dae::Scene>();
			dae::LevelManager::GetInstance().LoadLevel("lvl1.txt", *scene.get());
			dae::GameStateManager::GetInstance().Add(std::move(scene),1);
		}
		break;
		case MainMenuButtons::OPTIONS:
		{
			auto options = std::make_unique<Options>();
			dae::GameStateManager::GetInstance().Add(std::move(options));
		}
		break;
		}
	}
}

void MainMenu::Render() const
{
	

	auto& renderer = dae::Renderer::GetInstance();

	int windowWidth{ 0 };
	int windowHeight{ 0 };
	SDL_GetWindowSize(renderer.GetWindow(), &windowWidth, &windowHeight);


	glm::vec2 logoPos{ windowWidth / 2 - m_pLogoTexture->GetWidth() / 2 ,20 + m_pLogoTexture->GetHeight() };
	glm::vec2 playButtonPos{ windowWidth / 2 - m_pPlayButtonTexture->GetWidth() / 2 ,logoPos.y + m_pLogoTexture->GetHeight() + 40 + m_pPlayButtonTexture->GetHeight() };
	glm::vec2 optionsButtonPos{ windowWidth / 2 - m_pOptionsButtonTexture->GetWidth() / 2, playButtonPos.y + 20 + m_pOptionsButtonTexture->GetHeight() };

	renderer.RenderTexture(*m_pLogoTexture.get(), logoPos.x ,logoPos.y );
	renderer.RenderTexture(*m_pPlayButtonTexture.get(), playButtonPos.x, playButtonPos.y);
	renderer.RenderTexture(*m_pOptionsButtonTexture.get(), optionsButtonPos.x, optionsButtonPos.y);

	glm::vec2 iconPos{};
	int iconspacer{ 10 };
	int iconSizeMultiplier{ 2 };


	switch (m_ActiveButtonId)
	{
	case MainMenuButtons::OPTIONS:
		iconPos.x = optionsButtonPos.x - iconspacer - m_pPeterHeadIcon->GetWidth()*iconSizeMultiplier;
		iconPos.y = optionsButtonPos.y + m_pOptionsButtonTexture->GetHeight() / 2 - m_pPeterHeadIcon->GetHeight() / 2;
		break;
	case MainMenuButtons::PLAY:
		iconPos.x = playButtonPos.x - iconspacer - m_pPeterHeadIcon->GetWidth()*iconSizeMultiplier;
		iconPos.y = playButtonPos.y + m_pPlayButtonTexture->GetHeight() / 2 - m_pPeterHeadIcon->GetHeight() / 2;
		break;
	default:
		std::cerr << "Not all button positions are included.";
	}

	renderer.RenderTexture(*m_pPeterHeadIcon.get(), iconPos.x, iconPos.y, m_pPeterHeadIcon->GetWidth()*iconSizeMultiplier, m_pPeterHeadIcon->GetHeight() * iconSizeMultiplier);
}
