#include "MiniginPCH.h"
#include "Victory.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameStateManager.h"
#include "Scene.h"
#include "LevelManager.h"
#include "GameStateManager.h"
#include "Options.h"
#include "GlobalValues.h"
#include <numeric>


void Victory::ControllerUpdate()
{
	if (m_InputManagerRef.IsPressed(dae::ControllerButton::ButtonA, 0))
	{
		switch (m_ActiveButtonId)
		{
		case VictoryButtons::PLAY:
		{
			auto scene = std::make_unique<dae::Scene>(1);
			dae::LevelManager::GetInstance().LoadLevel("lvl1.txt", *scene.get());
			dae::GameStateManager::GetInstance().Add(std::move(scene), 1);
		}
		break;
		case VictoryButtons::QUIT:
		{
			auto options = std::make_unique<Options>();
			dae::GameStateManager::GetInstance().Add(std::move(options));
		}
		break;
		}
	}
}

void Victory::KeyboardUpdate()
{
	if (m_InputManagerRef.IsPressed(SDL_SCANCODE_RETURN))
	{
		switch (m_ActiveButtonId)
		{
		case VictoryButtons::PLAY:
		{
			auto scene = std::make_unique<dae::Scene>(1);
			dae::LevelManager::GetInstance().LoadLevel("lvl1.txt", *scene.get());
			dae::GameStateManager::GetInstance().Add(std::move(scene), 1);
		}
		break;
		case VictoryButtons::QUIT:
		{
			m_InputManagerRef.m_IsClosingProgram = true;
		}
		break;
		}
	}
}

Victory::Victory()
{
}

Victory::~Victory()
{
}

void Victory::Init()
{
	auto& resourceRef = dae::ResourceManager::GetInstance();

	m_pPeterHeadIcon = resourceRef.LoadTexture("PeterHead.png");
	auto font = resourceRef.LoadFont("pixel.otf", 20);
	m_pReplayButtonTexture = resourceRef.LoadTextureFromFont(font, "REPLAY");
	m_pQuitButtonTexture = resourceRef.LoadTextureFromFont(font, "QUIT");
	m_pVictoryTexture = resourceRef.LoadTextureFromFont(font, "VICTORY");


	std::string str{};
	if (GlobalValues::m_Scores.size() > 1)
		for (int i = 0; i < (int)GlobalValues::m_Scores.size(); ++i)
		{
			str = "Player " + std::to_string(i + 1) + " score: " + std::to_string(GlobalValues::m_Scores[i]);
			m_pScoreTextures.emplace_back(resourceRef.LoadTextureFromFont(font, str));
		}

	str = "Total score: " + std::to_string(std::accumulate(GlobalValues::m_Scores.begin(), GlobalValues::m_Scores.end(), 0));
	m_pScoreTextures.emplace_back(resourceRef.LoadTextureFromFont(font, str));
}

void Victory::HandleInput()
{
	auto j = dae::InputManager::GetInstance().GetMenuDirection(0);
	if (j == dae::Direction::Up)
		m_ActiveButtonId = VictoryButtons(((unsigned int)m_ActiveButtonId - 1) % (int)VictoryButtons::COUNT);
	if (j == dae::Direction::Down)
		m_ActiveButtonId = VictoryButtons(((unsigned int)m_ActiveButtonId + 1) % (int)VictoryButtons::COUNT);
}

void Victory::Update(const float)
{
	auto inDevice = m_InputManagerRef.GetInputDevice(0);
	if (inDevice == dae::InputDevices::KeyBoard)
		KeyboardUpdate();
	else if (inDevice == dae::InputDevices::XBoxController)
		ControllerUpdate();
}

void Victory::Render() const
{
	auto& renderer = dae::Renderer::GetInstance();

	int windowWidth{ 0 };
	int windowHeight{ 0 };
	SDL_GetWindowSize(renderer.GetWindow(), &windowWidth, &windowHeight);

	const int spacer{ 20 };

	glm::vec2 logoPos{ windowWidth / 2 - m_pVictoryTexture->GetWidth() / 2 ,20 + m_pVictoryTexture->GetHeight() };
	renderer.RenderTexture(*m_pVictoryTexture.get(), logoPos.x, logoPos.y);

	glm::vec2 scorePos{ 0,logoPos.y + m_pVictoryTexture->GetHeight() + spacer };

	for (int i = 0; i < (int)m_pScoreTextures.size(); ++i)
	{
		scorePos.x = windowWidth / 2 - m_pScoreTextures[i]->GetWidth() / 2;
		scorePos.y += i * (spacer + m_pScoreTextures[i]->GetHeight());
		renderer.RenderTexture(*m_pScoreTextures[i].get(), scorePos.x, scorePos.y);
	}

	glm::vec2 playButtonPos{ windowWidth / 2 - m_pReplayButtonTexture->GetWidth() / 2 ,scorePos.y + m_pScoreTextures[0]->GetHeight() + spacer*2 + m_pReplayButtonTexture->GetHeight() };
	glm::vec2 quitButtonPos{ windowWidth / 2 - m_pQuitButtonTexture->GetWidth() / 2, playButtonPos.y + spacer + m_pQuitButtonTexture->GetHeight() };

	renderer.RenderTexture(*m_pReplayButtonTexture.get(), playButtonPos.x, playButtonPos.y);
	renderer.RenderTexture(*m_pQuitButtonTexture.get(), quitButtonPos.x, quitButtonPos.y);

	glm::vec2 iconPos{};
	int iconspacer{ 10 };
	int iconSizeMultiplier{ 2 };


	switch (m_ActiveButtonId)
	{
	case VictoryButtons::QUIT:
		iconPos.x = quitButtonPos.x - iconspacer - m_pPeterHeadIcon->GetWidth() * iconSizeMultiplier;
		iconPos.y = quitButtonPos.y + m_pQuitButtonTexture->GetHeight() / 2 - m_pPeterHeadIcon->GetHeight() / 2;
		break;
	case VictoryButtons::PLAY:
		iconPos.x = playButtonPos.x - iconspacer - m_pPeterHeadIcon->GetWidth() * iconSizeMultiplier;
		iconPos.y = playButtonPos.y + m_pReplayButtonTexture->GetHeight() / 2 - m_pPeterHeadIcon->GetHeight() / 2;
		break;
	default:
		std::cerr << "Not all button positions are included.";
	}

	renderer.RenderTexture(*m_pPeterHeadIcon.get(), iconPos.x, iconPos.y, m_pPeterHeadIcon->GetWidth() * iconSizeMultiplier, m_pPeterHeadIcon->GetHeight() * iconSizeMultiplier);
}