#include "MiniginPCH.h"
#include "XBoxController.h"
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")

//IMPL
class dae::XBoxController::XInputImpl
{
	XINPUT_STATE* currentState{};
	XINPUT_STATE* lastState{};
public:
	XInputImpl();
	~XInputImpl();
	void ProcessInput();
	bool IsPressed(ControllerButton button, int controllerIdx) const;
	void GetLeftJoystickInput(int controllerIdx, int& XAxis, int& YAxis) const;
	void GetRightJoystickInput(int controllerIdx, int& XAxis, int& YAxis) const;
	bool IsDown(ControllerButton button) const;
	int GetMaxControllers() { return XUSER_MAX_COUNT; }
};

dae::XBoxController::XInputImpl::XInputImpl() :currentState(new XINPUT_STATE[XUSER_MAX_COUNT]), lastState(new XINPUT_STATE[XUSER_MAX_COUNT])
{
	ZeroMemory(currentState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
	ZeroMemory(lastState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
}

dae::XBoxController::XInputImpl::~XInputImpl()
{
	delete currentState;
	currentState = nullptr;

	delete lastState;
	lastState = nullptr;
}

void dae::XBoxController::XInputImpl::ProcessInput()
{
	std::swap(lastState, currentState);
	ZeroMemory(currentState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);

	for (int i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XInputGetState(i, &currentState[i]);
	}
}

bool dae::XBoxController::XInputImpl::IsPressed(ControllerButton button, int controllerIdx) const
{

	if (WORD(button) == currentState[controllerIdx].Gamepad.wButtons && lastState[controllerIdx].Gamepad.wButtons != currentState[controllerIdx].Gamepad.wButtons)
	{
		return true;
	}
	return false;
}


void dae::XBoxController::XInputImpl::GetLeftJoystickInput(int controllerIdx, int& XAxis, int& YAxis) const
{
	XAxis = currentState[controllerIdx].Gamepad.sThumbLX;
	YAxis = currentState[controllerIdx].Gamepad.sThumbLY;
}

void dae::XBoxController::XInputImpl::GetRightJoystickInput(int controllerIdx, int& XAxis, int& YAxis) const
{
	XAxis = currentState[controllerIdx].Gamepad.sThumbRX;
	YAxis = currentState[controllerIdx].Gamepad.sThumbRY;
}

bool dae::XBoxController::XInputImpl::IsDown(ControllerButton button) const
{
	for (int i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		if (WORD(button) == lastState[i].Gamepad.wButtons)
		{
			return true;
		}
	}
	return false;
}



//INPUT MANAGER

dae::XBoxController::XBoxController()
{
	m_pImpl = new XInputImpl();
}

dae::XBoxController::~XBoxController()
{
	delete m_pImpl;
	m_pImpl = nullptr;
}

void dae::XBoxController::ProcessInput() const
{
  m_pImpl->ProcessInput();
}

bool dae::XBoxController::IsPressed(ControllerButton button, int controllerIdx) const
{
	return m_pImpl->IsPressed(button, controllerIdx);
}

bool dae::XBoxController::IsDown(ControllerButton button) const
{
	return m_pImpl->IsDown(button);
}

void dae::XBoxController::GetLeftJoystickInput(int controllerIdx, int& XAxis, int& YAxis) const
{
	m_pImpl->GetLeftJoystickInput(controllerIdx, XAxis, YAxis);
}

void dae::XBoxController::GetRightJoystickInput(int controllerIdx, int& XAxis, int& YAxis) const
{
	m_pImpl->GetRightJoystickInput(controllerIdx, XAxis, YAxis);
}
