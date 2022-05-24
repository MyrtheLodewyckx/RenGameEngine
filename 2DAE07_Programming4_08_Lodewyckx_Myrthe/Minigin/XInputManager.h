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
		virtual std::pair<bool, int> IsPressed(ControllerButton button) const override;
		virtual bool IsDown(ControllerButton button) const override;

		virtual void HandleInputs() override;
	};
}