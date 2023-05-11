#include <SDL.h>
#include "InputManager.h"



bool dae::InputManager::ProcessInput(const float deltaTime)
{

	for(const auto& inputDevice: m_pControllers)
	{
		inputDevice->ProcessInput(deltaTime);
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
	}

	return true;
}

void dae::InputManager::AddController(std::shared_ptr<PlayerController> controller)
{
	m_pControllers.emplace_back(controller);
}


