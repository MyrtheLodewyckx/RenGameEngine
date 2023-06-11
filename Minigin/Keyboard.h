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
		~Keyboard();
		Keyboard(const Keyboard& other) = delete;
		Keyboard(Keyboard&& other) noexcept = delete;
		Keyboard& operator=(const Keyboard& other) = delete;
		Keyboard& operator=(Keyboard&& other)	noexcept = delete;

		void ProcessInput(const float deltaTime) const;
		bool IsPressed(SDL_Scancode key) const;
		bool IsDown(SDL_Scancode key) const;

		void AddCommand(SDL_Scancode key, KeyState state, Command* pKeyboard);
		void ClearCommands();
};

