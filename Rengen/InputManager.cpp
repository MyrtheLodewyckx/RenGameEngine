#include <SDL.h>
#include "InputManager.h"

#include "Keyboard.h"
#include "PlayerController.h"


dae::InputManager::InputManager()
{
	m_pKeyBoard = std::make_unique<Keyboard>();
}

bool dae::InputManager::ProcessInput(const float deltaTime)
{

	for(const auto& inputDevice: m_pControllers)
	{
		inputDevice->ProcessInput(deltaTime);
	}

	m_pKeyBoard->ProcessInput(deltaTime);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
	}

	return true;
}

void dae::InputManager::AddController(std::unique_ptr<PlayerController> controller)
{
	m_pControllers.emplace_back(std::move(controller));
}

PlayerController* dae::InputManager::GetController(int idx) const
{
	return m_pControllers[idx].get();
}

Keyboard* dae::InputManager::GetKeyboard() const
{
	return m_pKeyBoard.get();
}

void dae::InputManager::ClearControllers()
{
	m_pControllers.clear();
}

void dae::InputManager::ClearCommands() const
{
	for(const auto& controller: m_pControllers)
	{
		controller->ClearCommands();
	}
	m_pKeyBoard->ClearCommands();
}
