#pragma once
#include "Command.h"
#include <map>
#include "XBoxController.h"
#include "Keyboard.h"

namespace dae
{
	enum class InputDevices
	{
		XBoxController,
		KeyBoard
	};

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
		std::unique_ptr<Keyboard> m_pKeyBoard;

		static std::vector<InputDevices> m_InputDevices;

		static const int maxPlayers = 2;
		Direction m_direction[maxPlayers] = {};

		ThrowPepper* m_PepperCommand = new ThrowPepper{};
		Select* m_SelectCommand = new Select{};


		std::map<ControllerButton, Command*> m_ControllerCommandMap
		{
			{ControllerButton::ButtonA, m_SelectCommand},
			{ControllerButton::ButtonY,m_PepperCommand}
		};

		std::map<SDL_Scancode, Command*> m_Keyboard1CommandMap
		{
			{SDL_SCANCODE_R,m_PepperCommand},
			{SDL_SCANCODE_TAB, m_SelectCommand},
		};
		std::map<SDL_Scancode, Direction> m_Keyboard1DirectionMap
		{
			{SDL_SCANCODE_W,Direction::Up},
			{SDL_SCANCODE_A,Direction::Left},
			{SDL_SCANCODE_S,Direction::Down},
			{SDL_SCANCODE_D,Direction::Right}
		};

		std::map<SDL_Scancode, Command*> m_Keyboard2CommandMap
		{
			{SDL_SCANCODE_SPACE,m_PepperCommand},
			{SDL_SCANCODE_TAB, m_SelectCommand},
		};
		std::map<SDL_Scancode, Direction> m_Keyboard2DirectionMap
		{
			{SDL_SCANCODE_UP,Direction::Up},
			{SDL_SCANCODE_LEFT,Direction::Left},
			{SDL_SCANCODE_DOWN,Direction::Down},
			{SDL_SCANCODE_RIGHT,Direction::Right}
		};

		static int GetDeviceIdx(int playerIdx, InputDevices device);


	public:
		InputManager();
		~InputManager();

		void AddPlayer(InputDevices inputDevice);
		void RemovePlayer();
		void ChangePlayerInputDevice(int index, InputDevices newInputDevice);
		InputDevices GetInputDevice(int playerIdx);

		void SetDirection(int playerIdx, Direction direction) { m_direction[playerIdx] = direction; };

		std::map<ControllerButton, Command*> getCommandMap() { return m_ControllerCommandMap; };
		
		void SwitchCommand(ControllerButton newButton, Command* command);
		Direction GetPlayerDirection(int playerIdx) { return m_direction[playerIdx]; }

		bool ProcessInput();
		bool IsPressed(ControllerButton button, int PlayerIdx) const;
	/*	bool IsDown(ControllerButton button, int controllerIdx) const {}
		bool IsUp(ControllerButton button, int controllerIdx) const {}*/

		void HandleInputs();
	};
}



//IMPLEMENT FUNCTIONS!!!!!