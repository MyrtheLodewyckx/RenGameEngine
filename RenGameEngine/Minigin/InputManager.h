#pragma once
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

		DPAD_UP = 0x0001,
		DPAD_DOWN = 0x0002,
		DPAD_LEFT = 0x0004,
		DPAD_RIGHT = 0x0008,
		ButtonMenu = 0x0010
	};
	enum class Direction
	{
		None,
		Up,
		Down,
		Left,
		Right
	};

	class InputManager abstract
	{
	protected:

		static const int maxPlayers = 2;
		Direction m_direction[maxPlayers] = {};

		Jump* m_JumpCommand = new Jump{};
		Select* m_SingCommand = new Select{};
		Dance* m_DanceCommand = new Dance{};
		Die* m_DieCommand = new Die{};

		std::map<ControllerButton, Command*> m_ConsoleCommandMap
		{
			{ControllerButton::ButtonB,m_JumpCommand},
			{ControllerButton::ButtonA, m_SingCommand},
			{ControllerButton::ButtonY,m_DanceCommand},
			{ControllerButton::ButtonX, m_DieCommand}
		};

	public:
		InputManager() {}
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

		virtual bool ProcessInput() = 0;
		virtual bool IsPressed(ControllerButton button, int controllerIdx) const = 0;
		virtual bool IsDown(ControllerButton button) const = 0;

		virtual void HandleInputs() = 0;
	};


	//IS A CONTROLLER NOT AN INPUT MANAGER
	//COMPOSITION OVER INHERITANCE
	class XInputManager :public InputManager
	{
		class XInputImpl;
		XInputImpl* m_pImpl{};

	public:
		XInputManager();
		~XInputManager();

		virtual bool ProcessInput() override;
		bool IsPressed(ControllerButton button, int controllerIdx) const override;
		virtual bool IsDown(ControllerButton button) const override;
		 
		virtual void HandleInputs() override;
	};

	class InputServiceLocator
	{
		static InputManager* i_instance;

	public:
		InputServiceLocator() = delete;
		~InputServiceLocator() = delete;
		InputServiceLocator(const InputServiceLocator& other) = delete;
		InputServiceLocator(InputServiceLocator&& other) = delete;
		InputServiceLocator& operator=(const InputServiceLocator& other) = delete;
		InputServiceLocator& operator=(InputServiceLocator&& other) = delete;
		static InputManager& get_input_system()
		{
				return *i_instance;
		}
		static void register_Input(InputManager* ss)
		{
			i_instance = ss;
		}

		static bool ProcessInputs() 
		{
			return i_instance->ProcessInput();
		}

		static void HandleInputs()
		{
			i_instance->HandleInputs();
		}
	};
}



