#include "MiniginPCH.h"
#include "XInputManager.h"
#include "xinput.h"


#pragma comment(lib, "xinput.lib")

//IMPL
class dae::XInputManager::XInputImpl
{
	XINPUT_STATE* currentStates;
	XINPUT_STATE* lastStates;
	int m_PlayerMax{};

public:
	XInputImpl();
	bool ProcessInput();
	bool IsPressed(ControllerButton button, int idx) const;
	int GetPlayerMax() const { return m_PlayerMax; }
};

dae::XInputManager::XInputImpl::XInputImpl()
	:currentStates(new XINPUT_STATE[XUSER_MAX_COUNT])
	, lastStates(new XINPUT_STATE[XUSER_MAX_COUNT])
	,m_PlayerMax(XUSER_MAX_COUNT)
{
	ZeroMemory(currentStates, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
	ZeroMemory(lastStates, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
}

bool dae::XInputManager::XInputImpl::ProcessInput()
{
	lastStates = currentStates;
	ZeroMemory(currentStates, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
	for (int i = 0; i < XUSER_MAX_COUNT; ++i)
		XInputGetState(i, &currentStates[i]);

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

bool dae::XInputManager::XInputImpl::IsPressed(ControllerButton button, int idx) const
{
	if (WORD(button) == currentStates[idx].Gamepad.wButtons && lastStates[idx].Gamepad.wButtons != currentStates[idx].Gamepad.wButtons)
		return true;
	else return false;
}



//INPUT MANAGER
void dae::InputManager::AddPlayer(GameObject* player)
{
	m_Players.push_back(player);
}

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

bool dae::XInputManager::IsPressed(ControllerButton button, int idx) const
{
	return m_pImpl->IsPressed(button, idx);
}

void dae::XInputManager::HandleInputs()
{
	//assert(m_Players[0] != NULL);

	for (int i = 0; i < m_pImpl->GetPlayerMax(); ++i)
	{
		//A BUTTON
		if (IsPressed(ControllerButton::ButtonA, i))
			Input::GetInstance().GetCommand(ControllerButton::ButtonA)->Execute(m_Players[i]);

		//B BUTTON
		else if (IsPressed(ControllerButton::ButtonB, i))
			Input::GetInstance().GetCommand(ControllerButton::ButtonB)->Execute(m_Players[i]);

		//Y BUTTON
		else if (IsPressed(ControllerButton::ButtonY, i))
			Input::GetInstance().GetCommand(ControllerButton::ButtonY)->Execute(m_Players[i]);

		//X BUTTON
		else if (IsPressed(ControllerButton::ButtonX, i))
			Input::GetInstance().GetCommand(ControllerButton::ButtonX)->Execute(m_Players[i]);
	}
}