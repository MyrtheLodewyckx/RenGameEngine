#pragma once

#include <Windows.h>
#include "xinput.h"
#include <map>
#pragma comment(lib, "xinput.lib")
#include "Command.h"
#include "Singleton.h"


namespace dae
{
	

	enum class ControllerButton
	{
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,
		//todo: add the other buttons
	};

	enum class CommandEnum
	{
		Jump = XINPUT_GAMEPAD_A,
		Sing = XINPUT_GAMEPAD_B,
		Dance = XINPUT_GAMEPAD_Y,
		Die = XINPUT_GAMEPAD_X
	};

	class Input final: public Singleton<Input>
	{
		Jump* m_JumpCommand{};
		Sing* m_SingCommand{};
		Dance* m_DanceCommand{};
		Die* m_DieCommand{};

		std::map<ControllerButton, Command*> m_ConsoleCommand
		{
			{ControllerButton::ButtonA,m_JumpCommand},
			{ControllerButton::ButtonB, m_SingCommand},
			{ControllerButton::ButtonY,m_DanceCommand},
			{ControllerButton::ButtonX, m_DieCommand}
		};

	public:
		Command* GetCommand(ControllerButton Button)
		{
			return m_ConsoleCommand.find(Button)->second;
		}
	};
	


	class InputManager
	{
		XINPUT_STATE currentState{};
		int m_ControllerIdx{0};
	public:
		InputManager(int idx) :m_ControllerIdx(idx) {}
		void ProcessInput();
		bool IsPressed(ControllerButton button) const;

		void HandleInputs();
	};
}