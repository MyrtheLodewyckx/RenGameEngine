#pragma once
#include "Component.h"
#include <SpriteComponent.h>
#include <vector>

#include "GameObject.h"
#include "InputManager.h"
#include "Keyboard.h"
#include "Renderer.h"

enum class state
{
	neutral,
	win,
	lose
};

static state gGameState{ state::neutral };

enum class mode
{
	singlePlayer,
	co_up,
	versus
};


class PacManInstance final : public Component
{
	Keyboard* m_KeyboardRef{ dae::InputManager::GetInstance().GetKeyboard() };
	std::shared_ptr<dae::SpriteComponent> m_pBackGroundSprite{};
	void Win();
	float m_CurrentTime{};

	std::shared_ptr<dae::Texture2D> m_pReadyTexture;
	std::shared_ptr<dae::Texture2D> m_pGameOverTexture;

	dae::Renderer* m_pRendererRef{&dae::Renderer::GetInstance()};
	inline static int m_CurrentLevel{ 1 };
	inline static mode m_GameMode{ mode::singlePlayer };

public:
	explicit PacManInstance(dae::GameObject* go) :Component(go) {}
	~PacManInstance() override = default;

	static void SetMode(mode mode);
	static mode GetMode();

	static int GetCurrentLevel();

	virtual void Initialize() override;
	virtual void Update(const float) override;
	virtual void PostRender() const override;
	void SetBackGround(const dae::Sprite& pBackgroundSprite, int windowWidth, int windowHeight);
};
