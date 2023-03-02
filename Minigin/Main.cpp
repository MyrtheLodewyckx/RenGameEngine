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
#include "RotateComponent.h"


void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	auto textureComponent = go->AddComponent<TextureComponent>();
	textureComponent->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	textureComponent = go->AddComponent<TextureComponent>();
	textureComponent->SetTexture("logo.tga");
	go->SetPosition(216, 180,0);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<dae::GameObject>();
	textureComponent = go->AddComponent<TextureComponent>();
	auto txtComponent = go->AddComponent<textComponent>();
	txtComponent->SetFont(font);
	txtComponent->SetText("Programming 4 Assignment");
	go->SetPosition(87, 50, 0);
	scene.Add(go);

	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	go = std::make_shared<dae::GameObject>();
	textureComponent = go->AddComponent<TextureComponent>();
	txtComponent = go->AddComponent<textComponent>();
	txtComponent->SetFont(font);
	txtComponent->SetText("FPS");
	txtComponent->SetColor(SDL_Color(255, 0, 0));
	go->AddComponent<FPSComponent>();
	go->SetPosition(2, 2, 0);

	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	textureComponent = go->AddComponent<TextureComponent>();
	textureComponent->SetTexture("Sprites/Pacman.png");
	auto rotateComp = go->AddComponent<RotateComponent>();
	rotateComp->SetRotationPoint({300,300,0});
	rotateComp->RotateClockWise(false);
	rotateComp->SetRadius(50.f);
	scene.Add(go);

	auto child = std::make_shared<dae::GameObject>();
	textureComponent = child->AddComponent<TextureComponent>();
	textureComponent->SetTexture("Sprites/Cherry.png");
	rotateComp = child->AddComponent<RotateComponent>();
	rotateComp->SetRadius(20.f);
	scene.Add(child);

	child->SetParent(go);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}