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
#include "TransformComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	auto textureComponent = go->AddComponent<TextureComponent>();
	auto transformComponent = go->AddComponent<dae::TransformComponent>();
	textureComponent->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	textureComponent = go->AddComponent<TextureComponent>();
	textureComponent->SetTexture("logo.tga");
	transformComponent = go->AddComponent<dae::TransformComponent>();
	transformComponent->SetPosition(216, 180,0);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<dae::GameObject>();
	textureComponent = go->AddComponent<TextureComponent>();
	auto txtComponent = go->AddComponent<textComponent>();
	txtComponent->SetFont(font);
	txtComponent->SetText("Programming 4 Assignment");
	transformComponent = go->AddComponent<dae::TransformComponent>();
	transformComponent->SetPosition(87, 50, 0);
	scene.Add(go);

	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	go = std::make_shared<dae::GameObject>();
	textureComponent = go->AddComponent<TextureComponent>();
	txtComponent = go->AddComponent<textComponent>();
	txtComponent->SetFont(font);
	txtComponent->SetText("FPS");
	txtComponent->SetColor(SDL_Color(255, 0, 0));
	go->AddComponent<FPSComponent>();
	transformComponent = go->AddComponent<dae::TransformComponent>();
	transformComponent->SetPosition(2, 2, 0);

	scene.Add(go);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}