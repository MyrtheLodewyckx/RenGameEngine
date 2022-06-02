#include "MiniginPCH.h"
#include "Keyboard.h"

class dae::Keyboard::SDLInputImpl
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

dae::Keyboard::SDLInputImpl::SDLInputImpl()
{
	SDL_PollEvent(&currentState);
	SDL_PollEvent(&lastState);
}

dae::Keyboard::SDLInputImpl::~SDLInputImpl()
{
}

void dae::Keyboard::SDLInputImpl::ProcessInput()
{
	std::swap(lastState, currentState);
	SDL_PollEvent(&currentState);
}

bool dae::Keyboard::SDLInputImpl::IsPressed(SDL_Scancode key) const
{
	return (currentState.key.keysym.scancode == key && currentState.type == SDL_KEYDOWN);

	//return currentState[key];
}

bool dae::Keyboard::SDLInputImpl::IsDown(SDL_Scancode key) const
{
	return (currentState.key.keysym.scancode == key);
}


dae::Keyboard::Keyboard()
{
	m_pImpl = new SDLInputImpl();
}

dae::Keyboard::~Keyboard()
{
	delete m_pImpl;
	m_pImpl = nullptr;
}

void dae::Keyboard::ProcessInput() const
{
	m_pImpl->ProcessInput();
}

bool dae::Keyboard::IsPressed(SDL_Scancode key) const
{
	return m_pImpl->IsPressed(key);
}

bool dae::Keyboard::IsDown(SDL_Scancode key) const
{
	return m_pImpl->IsPressed(key);
}
