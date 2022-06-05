#pragma once
#include "GameState.h"
#include <string>
#include "Texture2D.h"
#include "Font.h"
#include "InputManager.h"
#include "GameStateManager.h"
#include "Renderer.h"

class Options : public dae::GameState
{
	
	std::shared_ptr<dae::Font> m_Font{};

	std::vector<std::shared_ptr<dae::Texture2D>> m_GameModeTexture{};
	std::vector<std::shared_ptr<dae::Texture2D>> m_InputDevicesTexture{};

	std::shared_ptr<dae::Texture2D> m_pArrowButtonTexture{};
	std::shared_ptr<dae::Texture2D> m_pPlayer1{};
	std::shared_ptr<dae::Texture2D> m_pPlayer2{};
	std::shared_ptr<dae::Texture2D> m_pPeterHeadIcon{};

	dae::InputManager& m_InputManagerRef{ dae::InputManager::GetInstance()};
	dae::GameMode& m_GameModeRef{ dae::GameStateManager::GetInstance().GetGameMode()};
	dae::Renderer& m_RendererRef{ dae::Renderer::GetInstance() };

	int m_Player1SelectedInputDevice{ 0 };
	int m_Player2SelectedInputDevice{ 0 };

	int m_lvls{ 0 };

	void ControllerUpdate();
	void KeyboardUpdate();

public:
	Options();
	~Options();

	void Init() override;
	void HandleInput() override;
	void Update(const float deltaTime) override;
	void Render() const override;
};