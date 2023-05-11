#pragma once
#include <map>
#include <SDL_scancode.h>
#include "PlayerController.h"


class Command;

class Keyboard: public PlayerController
{
	class SDLInputImpl;
	SDLInputImpl* m_pImpl{};
	std::map<SDL_Scancode, Command*> m_KeyboardCommandMap{};
public:
		Keyboard(dae::GameObject* go);
		~Keyboard() override;

		void ProcessInput(const float deltaTime) const override;
		bool IsPressed(SDL_Scancode key) const;
		bool IsDown(SDL_Scancode key) const;

		void AddCommand(SDL_Scancode key, Command* pCommand);
};

