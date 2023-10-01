#include "Controller.h"

#include <iostream>
#include <SDL_syswm.h>
#include <utility>
#include <Xinput.h>

#include "Command.h"
#pragma comment(lib, "xinput.lib")

//IMPL
class Controller::XInputImpl
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

	bool IsDown(ControllerButton button, int controllerIdx) const;
	int GetMaxControllers() { return XUSER_MAX_COUNT; }
};

Controller::XInputImpl::XInputImpl() :currentState(new XINPUT_STATE[XUSER_MAX_COUNT]), lastState(new XINPUT_STATE[XUSER_MAX_COUNT])
{
	ZeroMemory(currentState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
	ZeroMemory(lastState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
}

Controller::XInputImpl::~XInputImpl()
{
	delete currentState;
	currentState = nullptr;

	delete lastState;
	lastState = nullptr;
}

void Controller::XInputImpl::ProcessInput()
{
	std::swap(lastState, currentState);
	ZeroMemory(currentState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);

	for (int i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XInputGetState(i, &currentState[i]);
	}
}

bool Controller::XInputImpl::IsPressed(ControllerButton button, int controllerIdx) const
{

	if (WORD(button) == currentState[controllerIdx].Gamepad.wButtons && lastState[controllerIdx].Gamepad.wButtons != currentState[controllerIdx].Gamepad.wButtons)
	{
		return true;
	}
	return false;
}


void Controller::XInputImpl::GetLeftJoystickInput(int controllerIdx, int& XAxis, int& YAxis) const
{
	XAxis = currentState[controllerIdx].Gamepad.sThumbLX;
	YAxis = currentState[controllerIdx].Gamepad.sThumbLY;

	int length = (int)sqrt(XAxis * XAxis + YAxis * YAxis);
	if (length < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		XAxis = YAxis = 0;
}

void Controller::XInputImpl::GetRightJoystickInput(int controllerIdx, int& XAxis, int& YAxis) const
{
	XAxis = currentState[controllerIdx].Gamepad.sThumbRX;
	YAxis = currentState[controllerIdx].Gamepad.sThumbRY;

	int length = (int)sqrt(XAxis * XAxis + YAxis * YAxis);
	if (length < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		XAxis = YAxis = 0;
}

bool Controller::XInputImpl::IsDown(ControllerButton button, int controllerIdx) const
{
	if (WORD(button) == currentState[controllerIdx].Gamepad.wButtons)
	{
		return true;
	}
	return false;
}

//INPUT MANAGER

Controller::Controller()
	:PlayerController()
{
	m_ControllerIdx = m_AmtOfControllers;
	++m_AmtOfControllers;
	m_pImpl = new XInputImpl();
}

Controller::~Controller()
{
	std::cout << "destructor called";
	--m_AmtOfControllers;
	delete m_pImpl;
	m_pImpl = nullptr;
}

void Controller::ProcessInput(const float deltaTime) const
{
	m_pImpl->ProcessInput();

	for(const auto& button: m_ControllerCommandMap)
	{
		if (button.first == ControllerButton::LEFT_THUMB)
		{
			int x{};
			int y{};
			GetLeftJoystickInput(x, y);
			if (button.second.second && (abs(x) > 0.00001f || abs(y) > 0.00001f))
				button.second.second->Execute((float)x, (float)y, deltaTime);

			continue;
		}

		if (button.first == ControllerButton::RIGHT_THUMB)
		{
			int x{};
			int y{};
			GetRightJoystickInput(x, y);
			if (button.second.second && (abs(x) > 0.00001f || abs(y) > 0.00001f))
			button.second.second->Execute((float)x, (float)y, deltaTime);

			continue;
		}

		if(button.second.first == KeyState::IsPressed)
			if (IsPressed(button.first) && button.second.second)
			{
				button.second.second->Execute();
				continue;
			}

		if (button.second.first == KeyState::IsDown)
			if (IsDown(button.first) && button.second.second)
			{
				button.second.second->Execute();
			}
	}
}

bool Controller::IsPressed(ControllerButton button) const
{
	return m_pImpl->IsPressed(button, m_ControllerIdx);
}

bool Controller::IsDown(ControllerButton button) const
{
	return m_pImpl->IsDown(button, m_ControllerIdx);
}

void Controller::GetLeftJoystickInput(int& XAxis, int& YAxis) const
{
	m_pImpl->GetLeftJoystickInput(m_ControllerIdx, XAxis, YAxis);
}

void Controller::GetRightJoystickInput(int& XAxis, int& YAxis) const
{
	m_pImpl->GetRightJoystickInput(m_ControllerIdx, XAxis, YAxis);
}

void Controller::AddCommand(ControllerButton button, KeyState state, Command* pCommand)
{
	if (m_ControllerCommandMap.contains(button))
		m_ControllerCommandMap.erase(button);

		m_ControllerCommandMap.emplace(button, Button{ state, pCommand });
}

void Controller::ClearCommands()
{
	m_ControllerCommandMap.clear();
}
