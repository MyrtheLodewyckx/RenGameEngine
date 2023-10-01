#pragma once

#pragma once
#include <map>
#include <memory>

#include "PlayerController.h"


class Command;


	class Controller final : public PlayerController
	{
		class XInputImpl;
		XInputImpl* m_pImpl{};

		int m_ControllerIdx{};
		inline static int m_AmtOfControllers{ 0 };

		using Button = std::pair<KeyState, Command*>;
		std::map<ControllerButton, Button> m_ControllerCommandMap{};

	public:
		Controller();
		~Controller() override;
		Controller(const Controller& other) = delete;
		Controller(Controller&& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;

		virtual void ProcessInput(const float deltaTime) const override;
		virtual void AddCommand(ControllerButton button, KeyState state, Command* pCommand) override;
		virtual void ClearCommands() override;

		bool IsPressed(ControllerButton button) const;
		bool IsDown(ControllerButton button) const;

		void GetLeftJoystickInput(int& XAxis, int& YAxis) const;
		void GetRightJoystickInput(int& XAxis, int& YAxis) const;
	};