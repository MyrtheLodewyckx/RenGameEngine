#pragma once
#include <map>
#include <SDL_scancode.h>
#include "PlayerController.h"


class Command;

class Keyboard
{
	class SDLInputImpl;
	SDLInputImpl* m_pImpl{};
	using Button = std::pair<KeyState, Command*>;
	std::map<SDL_Scancode, Button> m_KeyboardCommandMap{};
public:
		Keyboard();
		~Keyboard() ;

		void ProcessInput(const float deltaTime) const;
		bool IsPressed(SDL_Scancode key) const;
		bool IsDown(SDL_Scancode key) const;

		void AddCommand(SDL_Scancode key, KeyState state, Command* pCommand);
		void ClearCommands();
};

