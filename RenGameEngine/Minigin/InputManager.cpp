#include "MiniginPCH.h"
#include "InputManager.h"
#include "xinput.h"
#include <SDL_events.h>
#include <algorithm>


std::vector<dae::InputDevices> dae::InputManager::m_InputDevices{ dae::InputDevices::KeyBoard };

int dae::InputManager::GetDeviceIdx(int playerIdx, InputDevices device)
{
	int Idx = 0;
	auto l = [&Idx, device](InputDevices i) { if (i == device) ++Idx; };
	std::for_each(m_InputDevices.begin(), m_InputDevices.begin() + playerIdx, l);
	return Idx;
}

dae::InputManager::InputManager()
{
	m_pXBox_controllers = std::make_unique<XBoxController>();
	m_pKeyBoard = std::make_unique<Keyboard>();
}

dae::InputManager::~InputManager()
{
	for (auto b : m_ControllerCommandMap)
	{
		delete b.second;
		b.second = nullptr;
	}
}

void dae::InputManager::AddPlayer(InputDevices inputD)
{
	m_InputDevices.emplace_back(inputD);
}

void dae::InputManager::RemovePlayer()
{
	m_InputDevices.pop_back();
}

void dae::InputManager::ChangePlayerInputDevice(int index, InputDevices newInputDevice)
{
	m_InputDevices[index] = newInputDevice;
}

dae::InputDevices dae::InputManager::GetInputDevice(int playerIdx)
{
	return m_InputDevices[playerIdx];
}

void dae::InputManager::SwitchCommand(ControllerButton, Command*)
{
	/*for (auto b : m_ControllerCommandMap)
	{
		if (b.first == newButton)
		{
			Command* lastCommand = b.second;
			b.second = command;

			for (auto c : m_ControllerCommandMap)
			{
				if (c.second == command)
					c.second = lastCommand;
				return;
			}
		}
	}*/
}

bool dae::InputManager::ProcessInput()
{
		m_pXBox_controllers->ProcessInput();
		m_pKeyBoard->ProcessInput();

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}

	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button, int playerIdx) const
{
	if (m_InputDevices[playerIdx] != InputDevices::XBoxController)
		return false;
	
	//Get the right controllerIDX for the player
	int controllerIdx = GetDeviceIdx(playerIdx, InputDevices::XBoxController);
	

	return m_pXBox_controllers->IsPressed(button, controllerIdx);
}

bool dae::InputManager::IsPressed(SDL_Scancode key) const
{
	return m_pKeyBoard->IsPressed(key);
}

void dae::InputManager::HandleInputs()
{
	//FIRST == BUTTON
	//SECOND == COMMAND

	const int joystickDeadZone = 32000;

	for (int i{ 0 }; i < m_InputDevices.size(); ++i)
	{
		m_direction[i] = Direction::None;
		m_MenuDirection[i] = Direction::None;

		//XBOX EXECUTION

		if (m_InputDevices[i] == InputDevices::XBoxController)
		{
			for (auto itr = m_ControllerCommandMap.begin(); itr != m_ControllerCommandMap.end(); itr++)
			{
				if (m_pXBox_controllers->IsPressed(itr->first, i))
				{
					itr->second->Execute(i);
					break;
				}
			}

			//SET DIRECTIONS
			int xAxis;
			int yAxis;
			m_pXBox_controllers->GetLeftJoystickInput(i, xAxis, yAxis);
			

			if (xAxis > joystickDeadZone || m_pXBox_controllers->IsDown(ControllerButton::DPAD_RIGHT,i))
			{
				m_direction[i] = Direction::Right;
			}
			else if (xAxis < -joystickDeadZone || m_pXBox_controllers->IsDown(ControllerButton::DPAD_LEFT, i))
			{
				m_direction[i] = Direction::Left;
			}

			if (yAxis > xAxis && yAxis > joystickDeadZone || m_pXBox_controllers->IsDown(ControllerButton::DPAD_UP, i))
			{
				m_direction[i] = Direction::Up;
			}
			else if (yAxis < xAxis && yAxis < -joystickDeadZone || m_pXBox_controllers->IsDown(ControllerButton::DPAD_DOWN, i))
			{
				m_direction[i] = Direction::Down;
			}

			//MENU DIRECTION

			if (m_pXBox_controllers->IsPressed(ControllerButton::DPAD_RIGHT, i))
			{
				m_MenuDirection[i] = Direction::Right;
			}
			else if (m_pXBox_controllers->IsDown(ControllerButton::DPAD_LEFT, i))
			{
				m_MenuDirection[i] = Direction::Left;
			}
			else if (m_pXBox_controllers->IsDown(ControllerButton::DPAD_UP, i))
			{
				m_MenuDirection[i] = Direction::Up;
			}
			else if (m_pXBox_controllers->IsDown(ControllerButton::DPAD_DOWN, i))
			{
				m_MenuDirection[i] = Direction::Down;
			}

		}

		//KEYBOARD EXECUTION PLAYER 1
		else if (m_InputDevices[i] == InputDevices::KeyBoard)
		{
			int keyboardIndex = GetDeviceIdx(i, InputDevices::KeyBoard);
			if (keyboardIndex == 0)
			{
				for (auto itr = m_Keyboard1CommandMap.begin(); itr != m_Keyboard1CommandMap.end(); itr++)
				{
					if (m_pKeyBoard->IsPressed(itr->first))
					{
						itr->second->Execute(i);
						break;
					}
				}
				for (auto itr = m_Keyboard1DirectionMap.begin(); itr != m_Keyboard1DirectionMap.end(); itr++)
				{
					if (m_pKeyBoard->IsDown(itr->first))
					{
					m_direction[i] = itr->second;
						break;
					}
				}
				for (auto itr = m_Keyboard1DirectionMap.begin(); itr != m_Keyboard1DirectionMap.end(); itr++)
				{
					if (m_pKeyBoard->IsPressed(itr->first))
					{
						m_MenuDirection[i] = itr->second;
						break;
					}
				}

			}
		//KEYBOARD EXECUTION PLAYER 2
			else
			{
				for (auto itr = m_Keyboard2CommandMap.begin(); itr != m_Keyboard2CommandMap.end(); itr++)
				{
					if (m_pKeyBoard->IsPressed(itr->first))
					{
						itr->second->Execute(i);
						break;
					}
				}
				for (auto itr = m_Keyboard2DirectionMap.begin(); itr != m_Keyboard2DirectionMap.end(); itr++)
				{
					if (m_pKeyBoard->IsDown(itr->first))
					{
						m_direction[i] = itr->second;
						break;
					}
				}
				for (auto itr = m_Keyboard2DirectionMap.begin(); itr != m_Keyboard2DirectionMap.end(); itr++)
				{
					if (m_pKeyBoard->IsPressed(itr->first))
					{
						m_MenuDirection[i] = itr->second;
						break;
					}
				}
			}

		}



	}
}
