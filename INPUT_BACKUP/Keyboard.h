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
		bool IsPressed(ControllerButton button, int controllerIdx) const;
		bool IsDown(ControllerButton button) const;
		void GetLeftJoystickInput(int controllerIdx, int& XAxis, int& YAxis) const;
		void GetRightJoystickInput(int controllerIdx, int& XAxis, int& YAxis) const;
	};
}