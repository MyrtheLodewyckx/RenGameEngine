#pragma once
#include "Component.h"

namespace dae
{
	class GameObject;
}

enum class KeyState
{
	IsPressed,
	IsDown,
	none
};

class PlayerController: public Component
{
protected:
	inline static int m_AmtOfPlayers{ 0 };
	int m_playerIdx{};

public:
	PlayerController(dae::GameObject* go);
	PlayerController(const PlayerController& other) = delete;
	PlayerController(PlayerController&& other) noexcept = delete;
	PlayerController& operator=(const PlayerController& other) = delete;
	PlayerController& operator=(PlayerController&& other)	noexcept = delete;

	virtual ~PlayerController() = default;
	virtual void ProcessInput(const float deltaTime) const = 0;
};
