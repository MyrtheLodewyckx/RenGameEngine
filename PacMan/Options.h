#pragma once
#include "Texture2D.h"
#include "Font.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Scene.h"
#include "TextComponent.h"
#include <TextureComponent.h>


class OptionsNavigate : public Command
{
public:
	OptionsNavigate(dae::GameObject* go) : Command(go) {}
	void Execute(float x, float y, const float deltaTime) override;
	bool m_CanRecieveInput{ true };
};

class OptionsNavigateLeft: public Command
{
public:
	OptionsNavigateLeft(dae::GameObject* go) : Command(go) {}
	void Execute() override;
};

class OptionsNavigateRight : public Command
{
public:
	OptionsNavigateRight(dae::GameObject* go) : Command(go) {}
	void Execute() override;
};

class OptionsReturn : public Command
{
public:
	OptionsReturn(dae::GameObject* go) : Command(go) {}
	void Execute() override;
};

class Options : public dae::Scene
{
	float m_CurrentTime{};
	float m_Delay{ 0.5f };

	int m_WindowWidth{};
	int m_WindowHeight{};
	
	std::shared_ptr<dae::Font> m_pFont{};

	std::shared_ptr<TextureComponent> m_pGameModeTexture{};
	std::shared_ptr<textComponent> m_pGameModeText{};
	std::shared_ptr<dae::GameObject> m_pGameModeObject{};
	std::shared_ptr<dae::Texture2D> m_pArrowButtonTexture{};

	std::unique_ptr<OptionsReturn> m_pReturnCommand{};
	std::unique_ptr<OptionsNavigate> m_pNavigateCommand{};
	std::unique_ptr<OptionsNavigateLeft> m_pNavigateLeftCommand{};
	std::unique_ptr<OptionsNavigateRight> m_pNavigateRightCommand{};

public:
	Options();
	~Options() override = default;
	Options(const Options& other) = delete;
	Options(Options&& other) noexcept = delete;
	Options& operator=(const Options& other) = delete;
	Options& operator=(Options&& other)	noexcept = delete;

	void Initialize() override;
	void Update(const float deltaTime) override;
};
