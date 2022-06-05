#pragma once
#include "GameState.h"
#include "Texture2D.h"
#include "Font.h"
#include <string>
#include "InputManager.h"


enum class GameOverButtons
{
	PLAY,
	QUIT,
	COUNT
};

class GameOver : public dae::GameState
{
	std::shared_ptr<dae::Texture2D> m_pVictoryTexture;
	std::shared_ptr<dae::Texture2D> m_pPeterHeadIcon;

	std::shared_ptr<dae::Texture2D> m_pReplayButtonTexture;
	std::shared_ptr<dae::Texture2D> m_pQuitButtonTexture;

	dae::InputManager& m_InputManagerRef{ dae::InputManager::GetInstance() };

	GameOverButtons m_ActiveButtonId{ GameOverButtons::PLAY };

	void ControllerUpdate();
	void KeyboardUpdate();

public:
	GameOver();
	~GameOver();

	void Init() override;
	void HandleInput() override;
	void Update(const float deltaTime) override;
	void Render() const override;
};