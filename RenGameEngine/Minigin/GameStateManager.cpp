#include "MiniginPCH.h"
#include "GameStateManager.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "Scene.h"

std::shared_ptr<dae::GameObject> dae::GameStateManager::CreateHUD(glm::vec3 pos, int controllerIdx) const
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("pixel.otf", 20);

	auto Hud = std::make_shared<GameObject>();
	auto player = Hud->AddComponent<HUD>();

	player->SetPlayerIdx(controllerIdx);

	//TEXT COMPONENT
	auto HUDTextCom = Hud->AddComponent<TextComponent>();
	std::string sHUDtext = "LIVES: " + std::to_string(player->GetLives());

	HUDTextCom->SetFont(font);
	HUDTextCom->SetText(sHUDtext);

	//TRANSFORM COMPONENT
	auto sHUDTransformCom = Hud->AddComponent<Transform>();
	sHUDTransformCom->SetPosition(pos);

	//TEXTURE COMPONENT
	Hud->AddComponent<TextureComponent>();

	//CHILD COMPONENT SCORE TEXT
	auto scoreHUD = std::make_shared<GameObject>();
	scoreHUD->SetParent(Hud.get());

	//TEXT COMPONENT
	auto scoreHUDTextCom = scoreHUD->AddComponent<TextComponent>();
	std::string scoreHUDtext = "SCORE: " + std::to_string(player->GetScore());
	 
	scoreHUDTextCom->SetFont(font);                                                                                 
	scoreHUDTextCom->SetText(scoreHUDtext);

	//TRANSFORM COMPONENT
	auto scoreHUDTransformCom = scoreHUD->AddComponent<Transform>();
	scoreHUDTransformCom->SetPosition(pos.x + 300, pos.y, pos.z);

	//TEXTURE COMPONENT
	scoreHUD->AddComponent<TextureComponent>();
}

dae::GameStateManager::GameStateManager()
{
	m_HUDs.emplace_back(HUDinfo());
}

dae::GameStateManager::~GameStateManager()
{
}

void dae::GameStateManager::SetGameMode(GameMode gameMode)
{
	m_GameMode = gameMode;
}

dae::GameMode& dae::GameStateManager::GetGameMode()
{
	return m_GameMode;
}

void dae::GameStateManager::Add(std::unique_ptr<GameState> toAdd, bool replace)
{
	m_add = true;
	m_newState = std::move(toAdd);
	m_replace = replace;
}

void dae::GameStateManager::PopCurrent()
{
	m_remove = true;
}

void dae::GameStateManager::ProcessStateChange()
{
	if (m_remove && !m_StateStack.empty())
	{
		m_StateStack.pop();

		if (!m_StateStack.empty())
			m_StateStack.top()->Start();

		m_remove = false;
	}

	if (m_add)
	{
		if (m_replace && !m_StateStack.empty())
		{
			m_StateStack.pop();
			m_replace = false;
		}

		if (!m_StateStack.empty())
		{
			m_StateStack.top()->Pause();
		}

		m_newState->Init();
		m_StateStack.push(std::move(m_newState));
		m_add = false;
	}
}

std::unique_ptr<dae::GameState>& dae::GameStateManager::GetCurrent()
{
	return m_StateStack.top();
}
