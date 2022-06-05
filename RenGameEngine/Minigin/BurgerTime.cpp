#include "MiniginPCH.h"


#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "MainMenu.h"
#include "GameStateManager.h"
#include "BurgerTimeCommands.h"
#include <SDL.h>

int main(int, char* []) {
	dae::Minigin engine;

	auto mainMenu = std::make_unique<MainMenu>();
	dae::GameStateManager::GetInstance().Add(std::move(mainMenu));

	ThrowPepper* m_PepperCommand = new ThrowPepper{};
	Select* m_SelectCommand = new Select{};


	auto& InputRef = dae::InputManager::GetInstance();
	InputRef.AddControllerMap(std::pair<dae::ControllerButton,Command*>(dae::ControllerButton::ButtonA, m_SelectCommand));
	InputRef.AddControllerMap(std::pair<dae::ControllerButton, Command*>(dae::ControllerButton::ButtonY, m_PepperCommand));
	InputRef.AddKeyboard1Map(std::pair<SDL_Scancode, Command*>(SDL_SCANCODE_R, m_PepperCommand));
	InputRef.AddKeyboard1Map(std::pair<SDL_Scancode, Command*>(SDL_SCANCODE_TAB, m_SelectCommand));
	InputRef.AddKeyboard2Map(std::pair<SDL_Scancode, Command*>(SDL_SCANCODE_SPACE, m_PepperCommand));
	InputRef.AddKeyboard2Map(std::pair<SDL_Scancode, Command*>(SDL_SCANCODE_TAB, m_SelectCommand));
	
	InputRef.AddKeyboard1DirectionMap(std::pair<SDL_Scancode,dae::Direction>(SDL_SCANCODE_W, Direction::Up));
	InputRef.AddKeyboard1DirectionMap(std::pair<SDL_Scancode, dae::Direction>(SDL_SCANCODE_A, Direction::Left));
	InputRef.AddKeyboard1DirectionMap(std::pair<SDL_Scancode, dae::Direction>(SDL_SCANCODE_S, Direction::Down));
	InputRef.AddKeyboard1DirectionMap(std::pair<SDL_Scancode, dae::Direction>(SDL_SCANCODE_D, Direction::Right));

	InputRef.AddKeyboard2DirectionMap(std::pair<SDL_Scancode, dae::Direction>(SDL_SCANCODE_UP, Direction::Up));
	InputRef.AddKeyboard2DirectionMap(std::pair<SDL_Scancode, dae::Direction>(SDL_SCANCODE_LEFT, Direction::Left));
	InputRef.AddKeyboard2DirectionMap(std::pair<SDL_Scancode, dae::Direction>(SDL_SCANCODE_DOWN, Direction::Down));
	InputRef.AddKeyboard2DirectionMap(std::pair<SDL_Scancode, dae::Direction>(SDL_SCANCODE_RIGHT, Direction::Right));

	engine.Run();
	return 0;
}