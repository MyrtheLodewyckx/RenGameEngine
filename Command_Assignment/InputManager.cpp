#include "InputManager.h"




void dae::InputManager::ProcessInput()
{
	// todo: read the input
	
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIdx, &currentState);
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	// todo: return whether the given button is pressed or not.
	return (WORD(button) == currentState.Gamepad.wButtons);
}

void dae::InputManager::HandleInputs()
{
	if (IsPressed(ControllerButton::ButtonA))
		Input::GetInstance().GetCommand(ControllerButton::ButtonA)->Execute();
	else if (IsPressed(ControllerButton::ButtonB))
		Input::GetInstance().GetCommand(ControllerButton::ButtonB)->Execute();
	else if (IsPressed(ControllerButton::ButtonY))
		Input::GetInstance().GetCommand(ControllerButton::ButtonY)->Execute();
	else if (IsPressed(ControllerButton::ButtonX))
		Input::GetInstance().GetCommand(ControllerButton::ButtonX)->Execute();
}

