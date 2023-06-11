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
#include "PacManSounds.h"
#include "SoundSystem.h"


dae::Scene* load()
{
	auto player1Controller = std::make_unique<Controller>();
	dae::InputManager::GetInstance().AddController(std::move(player1Controller));
	auto player2Controller = std::make_unique<Controller>();
	dae::InputManager::GetInstance().AddController(std::move(player2Controller));

	clips.emplace_back(AudioClip{ int(PacManSounds::PLAYER_DIES), "../Data/SoundEffects/Death.wav" });
	clips.emplace_back(AudioClip{ int(PacManSounds::MUNCH_1),"../Data/SoundEffects/Munch_1.wav" });
	clips.emplace_back(AudioClip{ int(PacManSounds::MUNCH_2),"../Data/SoundEffects/Munch_2.wav" });
	clips.emplace_back(AudioClip{ int(PacManSounds::EAT_FRUIT),"../Data/SoundEffects/Eat_Fruit.wav" });
	clips.emplace_back(AudioClip{ int(PacManSounds::EAT_GHOST),"../Data/SoundEffects/Eat_Ghost.wav" });
	clips.emplace_back(AudioClip{ int(PacManSounds::POWER_PELLET),"../Data/SoundEffects/Power_Pellet.wav" });
	clips.emplace_back(AudioClip{ int(PacManSounds::INTERMISSION),"../Data/SoundEffects/Intermission.wav" });

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