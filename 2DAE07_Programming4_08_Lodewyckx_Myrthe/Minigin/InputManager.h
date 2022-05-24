#pragma once
#include "Command.h"
#include <map>

namespace dae
{
	const int maxButtonsToChange = 4;

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
		ButtonMenu = 0x0010
	};

	class InputManager abstract
	{
	protected:
		int m_ControllerIdx{ 0 };

		Jump* m_JumpCommand = new Jump{};
		Select* m_SingCommand = new Select{};
		Dance* m_DanceCommand = new Dance{};
		Die* m_DieCommand = new Die{};

		Left* m_LeftCommand = new Left{};
		Right* m_RightCommand = new Right{};
		Up* m_UpCommand = new Up{};
		Down* m_DownCommand = new Down{};

		std::map<ControllerButton, Command*> m_ConsoleCommandMap
		{
			{ControllerButton::ButtonB,m_JumpCommand},
			{ControllerButton::ButtonA, m_SingCommand},
			{ControllerButton::ButtonY,m_DanceCommand},
			{ControllerButton::ButtonX, m_DieCommand}
		};

		std::map<ControllerButton, Command*> m_ConsoleCommandMapUnchangeable
		{
			{ControllerButton::DPAD_DOWN,m_DownCommand},
			{ControllerButton::DPAD_UP,m_UpCommand},
			{ControllerButton::DPAD_LEFT, m_LeftCommand},
			{ControllerButton::DPAD_RIGHT, m_RightCommand}
		};

	public:


		InputManager(int idx) :m_ControllerIdx(idx) {}
		~InputManager() 
		{
			for (auto b : m_ConsoleCommandMap)
			{
				delete b.second;
				b.second = nullptr;
			}
			for (auto b : m_ConsoleCommandMapUnchangeable)
			{
				delete b.second;
				b.second = nullptr;
			}
		}

		std::map<ControllerButton, Command*> getCommandMap() { return m_ConsoleCommandMap; };
		
		void SwitchCommand(ControllerButton newButton, Command* command) 
		{
			for (auto b : m_ConsoleCommandMap)
			{
				if (b.first == newButton)
				{
					Command* lastCommand = b.second;
					b.second = command;

					for (auto c : m_ConsoleCommandMap)
					{
						if (c.second == command)
							c.second = lastCommand;
						return;
					}
				}
			}
		};

		virtual bool ProcessInput() = 0;
		virtual std::pair<bool, int> IsPressed(ControllerButton button) const = 0;
		virtual bool IsDown(ControllerButton button) const = 0;
		
		virtual void HandleInputs() = 0;
	};
}




