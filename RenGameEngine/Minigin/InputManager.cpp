#include "MiniginPCH.h"
#include "InputManager.h"
#include "xinput.h"
#include <SDL_events.h>

bool dae::InputManager::ProcessInput()
{
	m_pXBox_controllers->ProcessInput();

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

bool dae::InputManager::IsPressed(ControllerButton button, int controllerIdx) const
{
	return m_pXBox_controllers->IsPressed(button, controllerIdx);
}

void dae::InputManager::HandleInputs()
{
	//FIRST == BUTTON
	//SECOND == COMMAND

	const int joystickDeadZone = 32000;

	for (int i{ 0 }; i < maxPlayers; ++i)
	{
		//EXECUTE BUTTON COMMANDS
		for (auto itr = m_ConsoleCommandMap.begin(); itr != m_ConsoleCommandMap.end(); itr++)
		{

			if (m_pXBox_controllers->IsPressed(itr->first, i))
			{
				itr->second->Execute(i);
				break;
			}
		}

		//SET JOYSTICK DIRECTION
		int xAxis;
		int yAxis;
		m_pXBox_controllers->GetLeftJoystickInput(i, xAxis, yAxis);
		m_direction[i] = Direction::None;


		if (xAxis > joystickDeadZone)
		{
			m_direction[i] = Direction::Right;
		}
		else if (xAxis < -joystickDeadZone)
		{
			m_direction[i] = Direction::Left;
		}

		if (yAxis > xAxis && yAxis > joystickDeadZone)
		{
			m_direction[i] = Direction::Up;
		}
		else if (yAxis < xAxis && yAxis < -joystickDeadZone)
		{
			m_direction[i] = Direction::Down;
		}

	}
}
