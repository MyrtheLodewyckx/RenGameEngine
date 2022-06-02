#include "MiniginPCH.h"
#include "Keyboard.h"

class dae::Keyboard::SDLInputImpl
{
	SDL_KeyboardEvent currentState{};
public:
	SDLInputImpl() = default;
	~SDLInputImpl() = default;
	void ProcessInput();
	bool IsPressed(ControllerButton button, int controllerIdx) const;
	void GetLeftJoystickInput(int controllerIdx, int& XAxis, int& YAxis) const;
	void GetRightJoystickInput(int controllerIdx, int& XAxis, int& YAxis) const;
	bool IsDown(ControllerButton button) const;
	int GetMaxControllers() { return XUSER_MAX_COUNT; }
};

dae::Keyboard::Keyboard()
{
}
