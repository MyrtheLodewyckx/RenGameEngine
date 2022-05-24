#include "MiniginPCH.h"
#include "XInputManager.h"
#include "xinput.h"
#include <SDL_events.h>

#pragma comment(lib, "xinput.lib")

//IMPL
class dae::XInputManager::XInputImpl
{
	XINPUT_STATE currentState{};
	XINPUT_STATE lastState{};
public:
	XInputImpl() = default;
	bool ProcessInput(int controllerIdx);
	bool IsPressed(ControllerButton button) const;
};

bool dae::XInputManager::XInputImpl::ProcessInput(int controllerIdx)
{
	lastState = currentState;
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(controllerIdx, &currentState);

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

bool dae::XInputManager::XInputImpl::IsPressed(ControllerButton button) const
{
	return (WORD(button) == currentState.Gamepad.wButtons && lastState.Gamepad.wButtons != currentState.Gamepad.wButtons);
}

//INPUT MANAGER

dae::XInputManager::XInputManager(int controllerIdx)
	:InputManager(controllerIdx)
{
	m_pImpl = new XInputImpl();
}

dae::XInputManager::~XInputManager()
{
	delete m_pImpl;
	m_pImpl = nullptr;
}

bool dae::XInputManager::ProcessInput()
{
	return m_pImpl->ProcessInput(m_ControllerIdx);
}

bool dae::XInputManager::IsPressed(ControllerButton button) const
{
	return m_pImpl->IsPressed(button);
}

void dae::XInputManager::HandleInputs()
{
	//A BUTTON
	if (IsPressed(ControllerButton::ButtonA))
		Input::GetInstance().GetCommand(ControllerButton::ButtonA)->Execute();

	//B BUTTON
	else if (IsPressed(ControllerButton::ButtonB))
		Input::GetInstance().GetCommand(ControllerButton::ButtonB)->Execute();

	//Y BUTTON
	else if (IsPressed(ControllerButton::ButtonY))
		Input::GetInstance().GetCommand(ControllerButton::ButtonY)->Execute();

	//X BUTTON
	else if (IsPressed(ControllerButton::ButtonX))
		Input::GetInstance().GetCommand(ControllerButton::ButtonX)->Execute();
}

