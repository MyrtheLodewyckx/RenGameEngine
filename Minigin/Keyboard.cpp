
#include "Keyboard.h"

#include <SDL_events.h>
#include <SDL_keyboard.h>
#include <utility>

class Keyboard::SDLInputImpl
{
	SDL_Event currentState{};
	SDL_Event lastState{};
public:
	SDLInputImpl();
	~SDLInputImpl();
	void ProcessInput();
	bool IsPressed(SDL_Scancode key) const;
	bool IsDown(SDL_Scancode key) const;
};

Keyboard::SDLInputImpl::SDLInputImpl()
{
	SDL_PollEvent(&currentState);
	SDL_PollEvent(&lastState);
}

Keyboard::SDLInputImpl::~SDLInputImpl()
= default;

void Keyboard::SDLInputImpl::ProcessInput()
{
	std::swap(lastState, currentState);
	SDL_PollEvent(&currentState);
}

bool Keyboard::SDLInputImpl::IsPressed(SDL_Scancode key) const
{
	return (currentState.key.keysym.scancode == key && currentState.type == SDL_KEYDOWN);
}

bool Keyboard::SDLInputImpl::IsDown(SDL_Scancode key) const
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	return keystate[key];
}


Keyboard::Keyboard()
{
	m_pImpl = new SDLInputImpl();
}

Keyboard::~Keyboard()
{
	delete m_pImpl;
	m_pImpl = nullptr;
}

void Keyboard::ProcessInput(const float) const
{
	m_pImpl->ProcessInput();

	for (const auto& button : m_KeyboardCommandMap)
	{
		if (button.second.first == KeyState::IsPressed)
			if (IsPressed(button.first))
			{
				if(button.second.second)
				button.second.second->Execute();
				continue;
			}

		if (button.second.first == KeyState::IsDown)
			if (IsDown(button.first))
			{
				if (button.second.second)
				button.second.second->Execute();
			}
	}
}

bool Keyboard::IsPressed(SDL_Scancode key) const
{
	return m_pImpl->IsPressed(key);
}

bool Keyboard::IsDown(SDL_Scancode key) const
{
	return m_pImpl->IsDown(key);
}

void Keyboard::AddCommand(SDL_Scancode key, KeyState state, Command* pCommand)
{
	if (m_KeyboardCommandMap.contains(key))
		m_KeyboardCommandMap.erase(key);

	m_KeyboardCommandMap.emplace(key, Button{ state, pCommand });
}

void Keyboard::ClearCommands()
{
	m_KeyboardCommandMap.clear();
}
