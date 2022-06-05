#pragma once

namespace dae
{
	enum class ControllerButton
	{
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,

		DPAD_UP = 0x0001,
		DPAD_DOWN = 0x0002,
		DPAD_LEFT = 0x0004,
		DPAD_RIGHT = 0x0008,
		ButtonMenu = 0x0010
	};

	class XBoxController
	{
		class XInputImpl;
		XInputImpl* m_pImpl{};

	public:
		XBoxController();
		~XBoxController();

		void ProcessInput() const;
		bool IsPressed(ControllerButton button, int controllerIdx) const;
		bool IsDown(ControllerButton button, int controllerIdx) const;
		void GetLeftJoystickInput(int controllerIdx, int& XAxis, int& YAxis) const;
		void GetRightJoystickInput(int controllerIdx, int& XAxis, int& YAxis) const;
		void GetJoystickEnterInputDirection(int controllerIdx, int& XAxis, int& YAxis) const;
	};
}