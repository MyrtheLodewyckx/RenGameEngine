#include "ResultScene.h"

#include "HUD.h"
#include "ResourceManager.h"
#include <Renderer.h>

#include "Texture2D.h"
#include "TextureComponent.h"

Results::Results()
	:Scene("Results")
{}

void Results::Initialize()
{
	auto go = std::make_shared<dae::GameObject>();

	auto font = dae::ResourceManager::GetInstance().LoadFont("Fonts/pixel.otf",50);
	auto resultsTexture = dae::ResourceManager::GetInstance().LoadTextureFromFont(font, "Score: " + std::to_string(gScore));

	go->AddComponent<TextureComponent>()->SetTexture(resultsTexture);

	int windowWidth{};
	int windowHeight{};
	SDL_GetWindowSize(dae::Renderer::GetInstance().get_window(), &windowWidth, &windowHeight);

	go->SetPosition(windowWidth * 0.5f - resultsTexture->GetSize().x * 0.5f, windowHeight * 0.5f - resultsTexture->GetSize().y * 0.5f,0);
	Add(go);
}
