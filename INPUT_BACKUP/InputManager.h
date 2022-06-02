#pragma once
#include "Command.h"
#include <map>
#include "XBoxController.h"

namespace dae
{
	enum class Direction
	{
		None,
		Up,
		Down,
		Left,
		Right
	};

	class InputManager: public Singleton<InputManager>
	{
	private:
		//ALL INPUT DEVICES
		std::unique_ptr<XBoxController> m_pXBox_controllers;

		static const int maxPlayers = 2;
		Direction m_direction[maxPlayers] = {};

		ThrowPepper* m_PepperCommand = new ThrowPepper{};
		Select* m_SingCommand = new Select{};
		Dance* m_DanceCommand = new Dance{};
		Die* m_DieCommand = new Die{};

		std::map<ControllerButton, Command*> m_ConsoleCommandMap
		{
			{ControllerButton::ButtonB,m_DanceCommand},
			{ControllerButton::ButtonA, m_SingCommand},
			{ControllerButton::ButtonY,m_PepperCommand},
			{ControllerButton::ButtonX, m_DieCommand}
		};

	public:
		InputManager()
		{
			m_pXBox_controllers = std::make_unique<XBoxController>();
		}
		~InputManager() 
		{
			for (auto b : m_ConsoleCommandMap)
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
		Direction GetJoystickDirection(int controllerIdx) { return m_direction[controllerIdx]; }

		bool ProcessInput();
		bool IsPressed(ControllerButton button, int controllerIdx) const;
	/*	bool IsDown(ControllerButton button, int controllerIdx) const {}
		bool IsUp(ControllerButton button, int controllerIdx) const {}*/

		void HandleInputs();
	};
}



//IMPLEMENT FUNCTIONS!!!!!