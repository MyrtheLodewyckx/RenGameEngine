#pragma once


namespace dae
{

	class Keyboard
	{
		class SDLInputImpl;
		SDLInputImpl* m_pImpl{};

	public:
		Keyboard();
		~Keyboard();

		void ProcessInput() const;
		bool IsPressed(SDL_Scancode key) const;
		bool IsDown(SDL_Scancode key) const;
	};
}