#include <vld.h>
#include <iostream>
#include <thread>
#include "InputManager.h"

using namespace dae;

int main()
{
	auto inputManager = InputManager(0);
	auto t = std::chrono::high_resolution_clock::now();

	while (true)
	{
		inputManager.ProcessInput();

		inputManager.HandleInputs();

		if (inputManager.IsPressed(ControllerButton::ButtonX))
			break;

		t += std::chrono::milliseconds(16); // we want 60 fps
		std::this_thread::sleep_until(t);
	}
	std::cout << "Let's end." << std::endl;

}
