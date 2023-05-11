
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
	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	return keystate[key];
}


Keyboard::Keyboard(dae::GameObject* go)
	:PlayerController(go)
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
}

bool Keyboard::IsPressed(SDL_Scancode key) const
{
	return m_pImpl->IsPressed(key);
}

bool Keyboard::IsDown(SDL_Scancode key) const
{
	return m_pImpl->IsDown(key);
}

void Keyboard::AddCommand(SDL_Scancode key, Command* pCommand)
{
	m_KeyboardCommandMap.try_emplace(key, pCommand);
}
