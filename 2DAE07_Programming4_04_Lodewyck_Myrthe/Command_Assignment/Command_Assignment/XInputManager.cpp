#include "XInputManager.h"
#include "xinput.h"
#include <minwinbase.h>
#include <vector>

#pragma comment(lib, "xinput.lib")

//IMPL
class dae::XInputManager::XInputImpl
{
	XINPUT_STATE* currentStates;
	XINPUT_STATE* lastStates;
public:
	XInputImpl();
	void ProcessInput(int controllerIdx);
	bool IsPressed(ControllerButton button) const;
};

dae::XInputManager::XInputImpl::XInputImpl()
	:currentStates(new XINPUT_STATE[XUSER_MAX_COUNT])
	,lastStates(new XINPUT_STATE[XUSER_MAX_COUNT])
{
	ZeroMemory(currentStates, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
	ZeroMemory(lastStates, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
}

void dae::XInputManager::XInputImpl::ProcessInput(int controllerIdx)
{
	lastStates = currentStates;
	ZeroMemory(currentStates, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
	for(int i = 0; i<XUSER_MAX_COUNT; ++i)
		auto result = XInputGetState(i, &currentStates[i]);
}

bool dae::XInputManager::XInputImpl::IsPressed(ControllerButton button) const
{
	for (int i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		if (WORD(button) == currentStates[i].Gamepad.wButtons && lastStates[i].Gamepad.wButtons != currentStates[i].Gamepad.wButtons)
			return true;
	}		

	return false;
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

void dae::XInputManager::ProcessInput()
{
	m_pImpl->ProcessInput(m_ControllerIdx);
}

bool dae::XInputManager::IsPressed(ControllerButton button) const
{
	return m_pImpl->IsPressed(button);
}

void dae::XInputManager::HandleInputs()
{
	//A BUTTON
	if (IsPressed(ControllerButton::ButtonA))
		GetCommand(ControllerButton::ButtonA)->Execute();

	//B BUTTON
	else if (IsPressed(ControllerButton::ButtonB))
		GetCommand(ControllerButton::ButtonB)->Execute();

	//Y BUTTON
	else if (IsPressed(ControllerButton::ButtonY))
		GetCommand(ControllerButton::ButtonY)->Execute();

	//X BUTTON
	else if (IsPressed(ControllerButton::ButtonX))
		GetCommand(ControllerButton::ButtonX)->Execute();
}

