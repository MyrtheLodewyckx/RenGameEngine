#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Controller.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "MainMenu.h"


dae::Scene* load()
{
	auto player1Controller = std::make_unique<Controller>();
	dae::InputManager::GetInstance().AddController(std::move(player1Controller));
	auto player2Controller = std::make_unique<Controller>();
	dae::InputManager::GetInstance().AddController(std::move(player2Controller));

	auto scene = std::make_unique<MainMenu>();
	dae::SceneManager::GetInstance().Add(std::move(scene));
	dae::SceneManager::GetInstance().ProcessStateChange();
	return scene.get();
}

int main(int, char* [])
{
	dae::Minigin engine("../Data/","PACMAN", 560, 760);


	engine.Run(load);
	return 0;
}