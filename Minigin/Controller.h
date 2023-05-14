#pragma once

#pragma once
#include <map>
#include <memory>

#include "PlayerController.h"


class Command;

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

	class Controller final : public PlayerController
	{
		class XInputImpl;
		XInputImpl* m_pImpl{};

		int m_ControllerIdx{};
		inline static int m_AmtOfControllers{ 0 };

		using Button = std::pair<ControllerButton,KeyState>;
		std::map<Button, std::unique_ptr<Command>> m_ControllerCommandMap{};

	public:
		Controller(dae::GameObject* go);
		~Controller() override;

		void ProcessInput(const float deltaTime) const override;

		bool IsPressed(ControllerButton button) const;
		bool IsDown(ControllerButton button) const;

		void GetLeftJoystickInput(int& XAxis, int& YAxis) const;
		void GetRightJoystickInput(int& XAxis, int& YAxis) const;

		void AddCommand(ControllerButton button, KeyState state, Command* pCommand);
	};