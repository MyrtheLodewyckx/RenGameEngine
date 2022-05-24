#pragma once
#include "InputManager.h"

namespace dae
{
	class XInputManager:public InputManager
	{
		class XInputImpl;
		XInputImpl* m_pImpl{};
		
	public:
		XInputManager(int controllerIdx);
		~XInputManager();

		virtual bool ProcessInput() override;
		virtual bool IsPressed(ControllerButton button) const override;

		virtual void HandleInputs() override;
	};
}