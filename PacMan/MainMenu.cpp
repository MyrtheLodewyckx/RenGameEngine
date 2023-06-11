#include "MainMenu.h"

#include <iostream>

#include "ResourceManager.h"
#include "Renderer.h"
#include "Scene.h"
#include "LevelManager.h"
#include "Options.h"
#include <Controller.h>


MainMenu::MainMenu():Scene("MainMenu")
{
	auto go = std::make_shared<dae::GameObject>();
	m_pNavigateCommand = std::make_shared<Navigate>(go.get());
	m_pSelectCommand = std::make_shared<Select>(go.get());
	m_pSelectCommand->m_pNavigate = m_pNavigateCommand.get();
	auto controller = dae::InputManager::GetInstance().GetController(0);
	controller->AddCommand(ControllerButton::LEFT_THUMB, KeyState::none, m_pNavigateCommand.get());
	controller->AddCommand(ControllerButton::ButtonA, KeyState::IsPressed, m_pSelectCommand.get());

	auto keyboard = dae::InputManager::GetInstance().GetKeyboard();
	keyboard->AddCommand(SDL_SCANCODE_W, KeyState::IsPressed, m_pNavigateCommand.get());
	keyboard->AddCommand(SDL_SCANCODE_S, KeyState::IsPressed, m_pNavigateCommand.get());

	keyboard->AddCommand(SDL_SCANCODE_RETURN, KeyState::IsPressed, m_pSelectCommand.get());

	Add(go);
}

MainMenu::~MainMenu()
{
}

void MainMenu::Start()
{
	auto controller = dae::InputManager::GetInstance().GetController(0);
	controller->AddCommand(ControllerButton::LEFT_THUMB, KeyState::none, m_pNavigateCommand.get());
	controller->AddCommand(ControllerButton::ButtonA, KeyState::IsPressed, m_pSelectCommand.get());

	auto keyboard = dae::InputManager::GetInstance().GetKeyboard();
	keyboard->AddCommand(SDL_SCANCODE_W, KeyState::IsPressed, m_pNavigateCommand.get());
	keyboard->AddCommand(SDL_SCANCODE_S, KeyState::IsPressed, m_pNavigateCommand.get());

	keyboard->AddCommand(SDL_SCANCODE_RETURN, KeyState::IsPressed, m_pSelectCommand.get());
}

void MainMenu::Initialize()
{

	m_pLogoTexture = dae::ResourceManager::GetInstance().LoadTexture("PacMan_Logo.png");
	m_pPacManIcon = dae::ResourceManager::GetInstance().LoadTexture("PacMan_Icon.png");
	auto font = dae::ResourceManager::GetInstance().LoadFont("Fonts/pixel.otf", 20);
	m_pOptionsButtonTexture = dae::ResourceManager::GetInstance().LoadTextureFromFont(font, "OPTIONS");
	m_pPlayButtonTexture = dae::ResourceManager::GetInstance().LoadTextureFromFont(font, "PLAY");
}


void MainMenu::Update(const float deltaTime)
{
	if (!m_pNavigateCommand->m_CanRecieveInput)
	{
		m_CurrentTime += deltaTime;
		if(m_CurrentTime >= m_Delay)
		{
			m_CurrentTime = 0;
			m_pNavigateCommand->m_CanRecieveInput = true;
		}
	}

}

void MainMenu::Render() const
{
	auto& renderer = dae::Renderer::GetInstance();

	int windowWidth{ 0 };
	int windowHeight{ 0 };
	SDL_GetWindowSize(renderer.get_window(), &windowWidth, &windowHeight);


	glm::vec2 logoPos{ windowWidth / 2 - m_pLogoTexture->GetSize().x / 2 ,20 + m_pLogoTexture->GetSize().y };
	glm::vec2 playButtonPos{ windowWidth / 2 - m_pPlayButtonTexture->GetSize().x / 2 ,logoPos.y + m_pLogoTexture->GetSize().y + 40 + m_pPlayButtonTexture->GetSize().y };
	glm::vec2 optionsButtonPos{ windowWidth / 2 - m_pOptionsButtonTexture->GetSize().x / 2, playButtonPos.y + 20 + m_pOptionsButtonTexture->GetSize().y };

	renderer.RenderTexture(*m_pLogoTexture.get(), logoPos.x ,logoPos.y );
	renderer.RenderTexture(*m_pPlayButtonTexture.get(), playButtonPos.x, playButtonPos.y);
	renderer.RenderTexture(*m_pOptionsButtonTexture.get(), optionsButtonPos.x, optionsButtonPos.y);

	glm::vec2 iconPos{};
	int iconspacer{ 10 };
	int iconSizeMultiplier{ 2 };


	switch (m_pNavigateCommand->m_ActiveButtonId)
	{
	case MainMenuButtons::OPTIONS:
		iconPos.x = optionsButtonPos.x - iconspacer - m_pPacManIcon->GetSize().x *iconSizeMultiplier;
		iconPos.y = optionsButtonPos.y + m_pOptionsButtonTexture->GetSize().y / 2 - m_pPacManIcon->GetSize().y / 2;
		break;
	case MainMenuButtons::PLAY:
		iconPos.x = playButtonPos.x - iconspacer - m_pPacManIcon->GetSize().x *iconSizeMultiplier;
		iconPos.y = playButtonPos.y + m_pPlayButtonTexture->GetSize().y / 2 - m_pPacManIcon->GetSize().y / 2;
		break;
	default:
		std::cerr << "Not all button positions are included.";
	}

	renderer.RenderTexture(*m_pPacManIcon.get(), iconPos.x, iconPos.y, (float)m_pPacManIcon->GetSize().x * iconSizeMultiplier, (float)m_pPacManIcon->GetSize().y * iconSizeMultiplier);
}

void Navigate::Execute()
{
	m_ActiveButtonId = MainMenuButtons(((unsigned int)m_ActiveButtonId - 1) % (int)MainMenuButtons::COUNT);
}

void Navigate::Execute(float, float, const float)
{
	if (!m_CanRecieveInput)
		return;

	m_CanRecieveInput = false;
	m_ActiveButtonId = MainMenuButtons(((unsigned int)m_ActiveButtonId - 1) % (int)MainMenuButtons::COUNT);
}

void Select::Execute()
{
	switch (m_pNavigate->m_ActiveButtonId)
	{
	case MainMenuButtons::PLAY:
	{
		auto scene = std::make_unique<dae::Scene>("Level 1");
		dae::LevelManager::GetInstance().LoadLevel(1, *scene);
		dae::SceneManager::GetInstance().Add(std::move(scene), true);
	}
	break;
	case MainMenuButtons::OPTIONS:
	{
		auto options = std::make_unique<Options>();
		dae::SceneManager::GetInstance().Add(std::move(options));
	}
	break;
	}
}
