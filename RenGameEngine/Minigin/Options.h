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
	std::vector<std::shared_ptr<dae::Texture2D>> m_GameModeTexture;
	std::shared_ptr<dae::Font> m_Font;
	std::shared_ptr<dae::Texture2D> m_pArrowButtonTexture;
	dae::InputManager& m_InputManagerRef{ dae::InputManager::GetInstance()};
	dae::GameMode& m_GameModeRef{ dae::GameStateManager::GetInstance().GetGameMode()};
	dae::Renderer& m_RendererRef{ dae::Renderer::GetInstance() };

public:
	Options();
	~Options();

	void Init() override;
	void HandleInput() override;
	void Update(const float deltaTime) override;
	void Render() const override;
};