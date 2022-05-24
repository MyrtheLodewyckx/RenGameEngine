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

		virtual void ProcessInput() override;
		virtual bool IsPressed(ControllerButton button) const override;

		virtual void HandleInputs() override;
	};
}