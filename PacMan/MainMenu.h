#pragma once
#include "Texture2D.h"
#include "Command.h"
#include "InputManager.h"
#include "Scene.h"

enum class MainMenuButtons
{
	PLAY,
	OPTIONS,
	COUNT
};


class Navigate: public Command
{
	public:
	Navigate(dae::GameObject* go) : Command(go) {}
	void Execute() override;
	void Execute(float, float, const float) override;
	bool m_CanRecieveInput{true};
	MainMenuButtons m_ActiveButtonId{ MainMenuButtons::PLAY };

};

class Select : public Command
{
public:
	Select(dae::GameObject* go) : Command(go) {}
	void Execute() override;
	Navigate* m_pNavigate{};
};

class MainMenu: public dae::Scene
{
	float m_CurrentTime{};
	float m_Delay{ 0.5f };

	std::shared_ptr<dae::Texture2D> m_pLogoTexture;
	std::shared_ptr<dae::Texture2D> m_pPacManIcon;
	std::shared_ptr<dae::Texture2D> m_pPlayButtonTexture;
	std::shared_ptr<dae::Texture2D> m_pOptionsButtonTexture;

	dae::InputManager& m_InputManagerRef{ dae::InputManager::GetInstance() };

	std::shared_ptr<Navigate> m_pNavigateCommand{};
	std::shared_ptr<Select> m_pSelectCommand{};

public:
	MainMenu();
	~MainMenu() override;
	MainMenu(const MainMenu& other) = delete;
	MainMenu(MainMenu&& other) noexcept = delete;
	MainMenu& operator=(const MainMenu& other) = delete;
	MainMenu& operator=(MainMenu&& other)	noexcept = delete;

	void Start() override;
	void Initialize() override;
	void Update(const float deltaTime) override;
	void Render() const override;
};