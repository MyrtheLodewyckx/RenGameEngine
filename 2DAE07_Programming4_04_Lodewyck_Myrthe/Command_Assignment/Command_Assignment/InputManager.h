#pragma once
#include "Input.h"
#include "Command.h"
#include <map>

namespace dae
{
	enum class ControllerButton
	{
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,
	};

	class InputManager abstract
	{
		Jump* m_JumpCommand = new Jump{};
		Sing* m_SingCommand = new Sing{};
		Dance* m_DanceCommand = new Dance{};
		Die* m_DieCommand = new Die{};

		std::map<ControllerButton, Command*> m_ConsoleCommand
		{
			{ControllerButton::ButtonB,m_JumpCommand},
			{ControllerButton::ButtonA, m_SingCommand},
			{ControllerButton::ButtonY,m_DanceCommand},
			{ControllerButton::ButtonX, m_DieCommand}
		};

	protected:
		int m_ControllerIdx{ 0 };

		Command* GetCommand(ControllerButton Button)
		{
			return m_ConsoleCommand.find(Button)->second;
		}

	public:

		InputManager(int idx) :m_ControllerIdx(idx) {}
		virtual void ProcessInput() = 0;
		virtual bool IsPressed(ControllerButton button) const = 0;
		
		virtual void HandleInputs() = 0;
	};
}




