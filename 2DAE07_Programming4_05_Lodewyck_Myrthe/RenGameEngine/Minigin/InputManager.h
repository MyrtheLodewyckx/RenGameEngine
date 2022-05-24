#pragma once
#include "Input.h"


namespace dae
{
	class InputManager abstract
	{
	protected:
		int m_ControllerIdx{ 0 };

	public:

		InputManager(int idx) :m_ControllerIdx(idx) {}
		virtual bool ProcessInput() = 0;
		virtual bool IsPressed(ControllerButton button) const = 0;
		
		virtual void HandleInputs() = 0;
	};
}




