#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "TextComponent.h"

using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");


	//ADD BACKGROUND
	auto texture = ResourceManager::GetInstance().LoadTexture("background.jpg");

	auto background = std::make_shared<GameObject>();

	auto textureCom = background->AddComponent<TextureComponent>();
	textureCom->SetTexture(texture);

	auto transformCom = background->AddComponent<Transform>();
	transformCom->SetPosition(0, 0, 0);

	scene.Add(background);


	//ADD LOGO
	auto logoTexture = ResourceManager::GetInstance().LoadTexture("logo.png");

	auto logo = std::make_shared<GameObject>();
	
	auto logoTextureComponent = logo->AddComponent<TextureComponent>();
	logoTextureComponent->SetTexture(logoTexture);

	auto logoTransformComponent = logo->AddComponent<Transform>();
	logoTransformComponent->SetPosition(216, 180, 0);

	scene.Add(logo);

	//ADD TEXT
	auto text = std::make_shared<GameObject>();

	auto textComponent = text->AddComponent<TextComponent>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	textComponent->SetFont(font);
	textComponent->SetText("Programming 4 Assignment");

	text->AddComponent<TextureComponent>();

	auto textTransformCom = text->AddComponent<Transform>();
	textTransformCom->SetPosition(80, 20, 0);
	scene.Add(text);

	//ADD PETER PEPPER
	auto peterPepper = std::make_shared<GameObject>();
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto timeLast = chrono::high_resolution_clock::now();

		while (doContinue)
		{
			//Get delta time
			auto timeNow = chrono::high_resolution_clock::now();
			auto deltaTime = timeNow - timeLast;

			doContinue = input.ProcessInput();
			sceneManager.Update(chrono::duration<float>(deltaTime).count());
			renderer.Render();

			//Update timeLast
			timeLast = timeNow;
		}
	}

	Cleanup();
}
