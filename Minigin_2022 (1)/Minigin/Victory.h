#pragma once
#include "GameState.h"
#include "Texture2D.h"
#include "Font.h"
#include <string>
#include "InputManager.h"


enum class VictoryButtons
{
	PLAY,
	QUIT,
	COUNT
};

class Victory : public dae::GameState
{
	std::shared_ptr<dae::Texture2D> m_pVictoryTexture;
	std::vector<std::shared_ptr<dae::Texture2D>> m_pScoreTextures;
	std::shared_ptr<dae::Texture2D> m_pPeterHeadIcon;

	std::shared_ptr<dae::Texture2D> m_pReplayButtonTexture;
	std::shared_ptr<dae::Texture2D> m_pQuitButtonTexture;

	dae::InputManager& m_InputManagerRef{ dae::InputManager::GetInstance() };

	VictoryButtons m_ActiveButtonId{ VictoryButtons::PLAY };

	void ControllerUpdate();
	void KeyboardUpdate();

public:
	Victory();
	~Victory();

	void Init() override;
	void HandleInput() override;
	void Update(const float deltaTime) override;
	void Render() const override;
};