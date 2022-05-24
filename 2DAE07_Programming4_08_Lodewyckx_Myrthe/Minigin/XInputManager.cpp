#include "MiniginPCH.h"
#include "XInputManager.h"
#include "xinput.h"
#include <SDL_events.h>

#pragma comment(lib, "xinput.lib")

//IMPL
class dae::XInputManager::XInputImpl
{
	XINPUT_STATE* currentState{};
	XINPUT_STATE* lastState{};
public:
	XInputImpl();
	~XInputImpl();
	bool ProcessInput();
	std::pair<bool, int> IsPressed(ControllerButton button) const;
	bool IsDown(ControllerButton button) const;
};

dae::XInputManager::XInputImpl::XInputImpl():currentState(new XINPUT_STATE[XUSER_MAX_COUNT]), lastState(new XINPUT_STATE[XUSER_MAX_COUNT])
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

std::pair<bool, int> dae::XInputManager::XInputImpl::IsPressed(ControllerButton button) const
{
	for (int i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		if (WORD(button) == currentState[i].Gamepad.wButtons && lastState[i].Gamepad.wButtons != currentState[i].Gamepad.wButtons)
		{
			return { true,i };
		}
	}
	return {false, 0};
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
	return m_pImpl->ProcessInput();
}

std::pair<bool,int> dae::XInputManager::IsPressed(ControllerButton button) const
{
	return m_pImpl->IsPressed(button);
}

bool dae::XInputManager::IsDown(ControllerButton button) const
{
	return m_pImpl->IsDown(button);
}

void dae::XInputManager::HandleInputs()
{
	//FIRST == BUTTON
	//SECOND == COMMAND

	for (auto itr = m_ConsoleCommandMap.begin(); itr != m_ConsoleCommandMap.end();itr++)
	{
		auto b = IsPressed(itr->first);
		if (b.first)
		{
			itr->second->Execute(b.second);
			break;
		}
		else
		{

		}
	}
}

