#include "MiniginPCH.h"
#include "Options.h"
#include "ResourceManager.h"



Options::Options()
{
}

Options::~Options()
{
}

void Options::Init()
{
	m_Font = dae::ResourceManager::GetInstance().LoadFont("pixel.otf", 20);
	m_pArrowButtonTexture = dae::ResourceManager::GetInstance().LoadTexture("Arrow.png");


	m_GameModeTexture.emplace_back(dae::ResourceManager::GetInstance().LoadTextureFromFont(m_Font, "SINGLE PLAYER"));
	m_GameModeTexture.emplace_back(dae::ResourceManager::GetInstance().LoadTextureFromFont(m_Font, "CO-UP"));
	m_GameModeTexture.emplace_back(dae::ResourceManager::GetInstance().LoadTextureFromFont(m_Font, "VERSUS"));

	m_GameModeTexture.shrink_to_fit();
}

void Options::HandleInput()
{
	auto j = m_InputManagerRef.GetJoystickDirection(0);

	if(j == dae::Direction::Left || m_InputManagerRef.IsPressed(dae::ControllerButton::DPAD_LEFT, 0))
	{
		m_GameModeRef = dae::GameMode(((int)m_GameModeRef - 1) % m_GameModeTexture.size());
	}
	else if(j == dae::Direction::Right || m_InputManagerRef.IsPressed(dae::ControllerButton::DPAD_RIGHT, 0))
	{
		m_GameModeRef = dae::GameMode(((int)m_GameModeRef + 1) % m_GameModeTexture.size());
	}
}

void Options::Update(const float)
{
	if (m_InputManagerRef.IsPressed(dae::ControllerButton::ButtonB, 0))
		dae::GameStateManager::GetInstance().PopCurrent();
}

void Options::Render() const
{
	int spacer = 10;
	int windowWidth{ 0 };
	int windowHeight{ 0 };
	SDL_GetWindowSize(m_RendererRef.GetWindow(), &windowWidth, &windowHeight);

	glm::vec2 gameModePos{ windowWidth/2 - m_GameModeTexture[(int)m_GameModeRef]->GetWidth() / 2, windowHeight/2 - m_GameModeTexture[(int)m_GameModeRef]->GetHeight() / 2 };
	m_RendererRef.RenderTexture(*m_GameModeTexture[(int)m_GameModeRef].get(), gameModePos.x, gameModePos.y);

	m_RendererRef.RenderTexture(*m_pArrowButtonTexture.get(), gameModePos.x - spacer - m_pArrowButtonTexture->GetWidth()*2, gameModePos.y, m_GameModeTexture[(int)m_GameModeRef]->GetHeight(), m_GameModeTexture[(int)m_GameModeRef]->GetHeight(),SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
	m_RendererRef.RenderTexture(*m_pArrowButtonTexture.get(), gameModePos.x + spacer + m_GameModeTexture[(int)m_GameModeRef]->GetWidth(), gameModePos.y, m_GameModeTexture[(int)m_GameModeRef]->GetHeight(), m_GameModeTexture[(int)m_GameModeRef]->GetHeight());
}
