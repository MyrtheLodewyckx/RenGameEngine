#pragma once
#include "Command.h"
#include <map>
#include "XBoxController.h"
#include "Keyboard.h"
#include "Singleton.h"

namespace dae
{
	enum class InputDevices
	{
		KeyBoard,
		XBoxController
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
		Direction m_MenuDirection[maxPlayers] = {};


		std::map<ControllerButton, Command*> m_ControllerCommandMap{};

		std::map<SDL_Scancode, Command*> m_Keyboard1CommandMap{};
		std::map<SDL_Scancode, Direction> m_Keyboard1DirectionMap{};

		std::map<SDL_Scancode, Command*> m_Keyboard2CommandMap{};
		std::map<SDL_Scancode, Direction> m_Keyboard2DirectionMap{};

		static int GetDeviceIdx(int playerIdx, InputDevices device);


	public:
		bool m_IsClosingProgram = false;

		InputManager();
		~InputManager();

		void AddControllerMap(std::pair<ControllerButton, Command*> map) { m_ControllerCommandMap.emplace(map); }
		void AddKeyboard1Map(std::pair<SDL_Scancode, Command*> map) { m_Keyboard1CommandMap.emplace(map); }
		void AddKeyboard2Map(std::pair<SDL_Scancode, Command*> map) { m_Keyboard2CommandMap.emplace(map); }
		void AddKeyboard1DirectionMap(std::pair<SDL_Scancode, Direction> map) { m_Keyboard1DirectionMap.emplace(map); }
		void AddKeyboard2DirectionMap(std::pair<SDL_Scancode, Direction> map) { m_Keyboard2DirectionMap.emplace(map); }

		void AddPlayer(InputDevices inputDevice);
		void RemovePlayer();
		void ChangePlayerInputDevice(int index, InputDevices newInputDevice);
		InputDevices GetInputDevice(int playerIdx);
		int GetAmtOfPlayers() { return (int)m_InputDevices.size(); }

		void SetDirection(int playerIdx, Direction direction) { m_direction[playerIdx] = direction; };

		std::map<ControllerButton, Command*> getCommandMap() { return m_ControllerCommandMap; };
		
		void SwitchCommand(ControllerButton newButton, Command* command);
		Direction GetPlayerDirection(int playerIdx) { return m_direction[playerIdx]; }
		Direction GetMenuDirection(int playerIdx) { return m_MenuDirection[playerIdx]; }

		bool ProcessInput();
		bool IsPressed(ControllerButton button, int PlayerIdx) const;
		bool IsPressed(SDL_Scancode key) const;
	/*	bool IsDown(ControllerButton button, int controllerIdx) const {}
		bool IsUp(ControllerButton button, int controllerIdx) const {}*/

		void HandleInputs();
	};
}



//IMPLEMENT FUNCTIONS!!!!!