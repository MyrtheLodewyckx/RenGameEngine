#pragma once
#include "Command.h"
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

enum class ControllerButton
{
	ButtonA = 0x1000,
	ButtonB = 0x2000,
	ButtonX = 0x4000,
	ButtonY = 0x8000,

	DPAD_UP = 0x0001,
	DPAD_DOWN = 0x0002,
	DPAD_LEFT = 0x0004,
	DPAD_RIGHT = 0x0008,
	ButtonMenu = 0x0010,

	LEFT_THUMB = 0x0040,
	RIGHT_THUMB = 0x0080
};

class PlayerController
{
protected:
	inline static int m_AmtOfPlayers{ 0 };
	int m_playerIdx{};

public:
	PlayerController();
	PlayerController(const PlayerController& other) = delete;
	PlayerController(PlayerController&& other) noexcept = delete;
	PlayerController& operator=(const PlayerController& other) = delete;
	PlayerController& operator=(PlayerController&& other)	noexcept = delete;

	virtual ~PlayerController() = default;
	virtual void ProcessInput(const float deltaTime) const = 0;
	virtual void AddCommand(ControllerButton button, KeyState state, Command* pCommand) = 0;
	virtual void ClearCommands() = 0;
};
