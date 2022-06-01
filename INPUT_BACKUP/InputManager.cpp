#include "MiniginPCH.h"
#include "InputManager.h"
#include "xinput.h"
#include <SDL_events.h>

#pragma comment(lib, "xinput.lib")


dae::InputManager* dae::InputServiceLocator::i_instance;

//IMPL
class dae::XInputManager::XInputImpl
{
	XINPUT_STATE* currentState{};
	XINPUT_STATE* lastState{};
public:
	XInputImpl();
	~XInputImpl();
	bool ProcessInput();
	bool IsPressed(ControllerButton button, int controllerIdx) const;
	std::pair<int, int> GetLeftJoystickInput(int controllerIdx) const;
	std::pair<int, int> GetRightJoystickInput(int controllerIdx) const;
	bool IsDown(ControllerButton button) const;
	int GetMaxControllers() { return XUSER_MAX_COUNT; }
};

dae::XInputManager::XInputImpl::XInputImpl() :currentState(new XINPUT_STATE[XUSER_MAX_COUNT]), lastState(new XINPUT_STATE[XUSER_MAX_COUNT])
{
	ZeroMemory(currentState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
	ZeroMemory(lastState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
}

dae::XInputManager::XInputImpl::~XInputImpl()
{
	delete currentState;
	currentState = nullptr;

	delete lastState;
	lastState = nullptr;
}

bool dae::XInputManager::XInputImpl::ProcessInput()
{
	std::swap(lastState, currentState);
	ZeroMemory(currentState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);

	for (int i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XInputGetState(i, &currentState[i]);
	}

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

bool dae::XInputManager::XInputImpl::IsPressed(ControllerButton button, int controllerIdx) const
{

	if (WORD(button) == currentState[controllerIdx].Gamepad.wButtons && lastState[controllerIdx].Gamepad.wButtons != currentState[controllerIdx].Gamepad.wButtons)
	{
		return true;
	}
	return false;
}


std::pair<int, int> dae::XInputManager::XInputImpl::GetLeftJoystickInput(int controllerIdx) const
{
	std::pair<int, int> JoyStickCoordinates{};
	JoyStickCoordinates.first = currentState[controllerIdx].Gamepad.sThumbLX;
	JoyStickCoordinates.second = currentState[controllerIdx].Gamepad.sThumbLY;
	return JoyStickCoordinates;
}

std::pair<int, int> dae::XInputManager::XInputImpl::GetRightJoystickInput(int controllerIdx) const
{
	std::pair<int, int> JoyStickCoordinates{};
	JoyStickCoordinates.first = currentState[controllerIdx].Gamepad.sThumbRX;
	JoyStickCoordinates.second = currentState[controllerIdx].Gamepad.sThumbRY;
	return JoyStickCoordinates;
}

bool dae::XInputManager::XInputImpl::IsDown(ControllerButton button) const
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

dae::XInputManager::XInputManager()
	:InputManager()
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
	return m_pImpl->ProcessInput();
}

bool dae::XInputManager::IsPressed(ControllerButton button, int controllerIdx) const
{
	return m_pImpl->IsPressed(button, controllerIdx);
}

bool dae::XInputManager::IsDown(ControllerButton button) const
{
	return m_pImpl->IsDown(button);
}

void dae::XInputManager::HandleInputs()
{
	//FIRST == BUTTON
	//SECOND == COMMAND

	const int joystickDeadZone = 5000;

	for (int i{ 0 }; i < maxPlayers; ++i)
	{
		//EXECUTE BUTTON COMMANDS
		for (auto itr = m_ConsoleCommandMap.begin(); itr != m_ConsoleCommandMap.end(); itr++)
		{

			if (m_pImpl->IsPressed(itr->first, i))
			{
				itr->second->Execute(i);
				break;
			}
		}


		//SET JOYSTICK DIRECTION
		auto joystickInput = m_pImpl->GetLeftJoystickInput(i);
		m_direction[i] = Direction::None;


		if (joystickInput.first > joystickDeadZone)
		{
			m_direction[i] = Direction::Right;
		}
		else if (joystickInput.first < -joystickDeadZone)
		{
			m_direction[i] = Direction::Left;
		}

		if (joystickInput.second > joystickInput.first && joystickInput.second > joystickDeadZone)
		{
			m_direction[i] = Direction::Up;
		}
		else if (joystickInput.second < joystickInput.first && joystickInput.second < -joystickDeadZone)
		{
			m_direction[i] = Direction::Down;
		}

	}
}