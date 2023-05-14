#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "PacMan.h"
#include "Renderer.h"


dae::Scene* load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");



	auto font = dae::ResourceManager::GetInstance().LoadFont("Fonts/pixel.otf", 20);
	auto go = std::make_shared<dae::GameObject>();
	auto textureComponent = go->AddComponent<TextureComponent>();
	auto txtComponent = go->AddComponent<textComponent>();
	txtComponent->SetFont(font);
	txtComponent->SetText("FPS");
	txtComponent->SetColor(SDL_Color(255,0,0));
	go->AddComponent<FPSComponent>();
	go->SetPosition(2, 2, 0);
	scene.Add(go);

	//PACMAN

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<PacMan>();
	go->SetPosition(0, 0, 0);
	scene.Add(go);


	return &scene;
}

int main(int, char* [])
{
	dae::Minigin engine("../Data/", "Programming 4: PACMAN");
	engine.Run(load);
	return 0;
}