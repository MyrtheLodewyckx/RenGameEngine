#pragma once
#include "GameState.h"
#include "Texture2D.h"
#include "Font.h"
#include <string>

enum class MainMenuButtons
{
	PLAY,
	OPTIONS,
	COUNT
};


class MainMenu: public dae::GameState
{
	std::shared_ptr<dae::Texture2D> m_pLogoTexture;
	std::shared_ptr<dae::Texture2D> m_pPeterHeadIcon;

	std::shared_ptr<dae::Texture2D> m_pPlayButtonTexture;
	std::shared_ptr<dae::Texture2D> m_pOptionsButtonTexture;

	MainMenuButtons m_ActiveButtonId{MainMenuButtons::PLAY};

public:
	MainMenu();
	~MainMenu();

	void Init() override;
	void HandleInput() override;
	void Update(const float deltaTime) override;
	void Render() const override;
};