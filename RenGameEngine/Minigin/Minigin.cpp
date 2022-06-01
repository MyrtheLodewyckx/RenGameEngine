#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "Player.h"
#include "EventManager.h"
#include "SpriteComponent.h"
#include "FPScounter.h"
#include "Audio.h"
#include "InputManager.h"
#include "PlayerPhysics.h"
#include "Ladder.h"
#include "Platform.h"
#include "BurgerPart.h"
#include "LevelManager.h"
#include "GameStateManager.h"
#include "MainMenu.h"
#include "Options.h"

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
		620,
		800,
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
	//auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	
	//auto scene = std::make_unique<Scene>();
	//int windowWidth{};
	//int windowHeight{};
	//SDL_GetWindowSize(m_Window, &windowWidth, &windowHeight);
	//auto font = ResourceManager::GetInstance().LoadFont("pixel.otf", 20);

	//auto backgroundParent = std::make_shared<GameObject>();

	////ADD FPS COUNTER
	//auto fps = std::make_shared<GameObject>();

	//auto fpsText = fps->AddComponent<TextComponent>();
	//fpsText->SetFont(font);
	//fpsText->SetText("0 FPS");

	//fps->AddComponent<TextureComponent>();

	//auto fpsPos = fps->AddComponent<Transform>();
	//fpsPos->SetPosition(10, 20, 0);

	//fps->AddComponent<FPSCounter>();

	//scene->Add(fps);

	//LevelManager::GetInstance().LoadLevel("lvl1.txt",*scene.get());
	////ADD PETER PEPPER HUD
	//CreateHUD(glm::vec3(100,10, 0), scene.get(), 0);

	////ADD PETER PEPPER
	//CreatePlayer(glm::vec3(240, 599, 0), scene.get(), 0);

	//GameStateManager::GetInstance().Add(std::move(scene));
	//GameStateManager::GetInstance().ProcessStateChange();

	auto mainMenu = std::make_unique<MainMenu>();
	GameStateManager::GetInstance().Add(std::move(mainMenu));
	GameStateManager::GetInstance().ProcessStateChange();


	//ADD SALLY SALT HUD
	//CreateHUD(glm::vec3((float)windowWidth - 170, 200, 0), scene, 1);

	//ADD SALLY SALT
	//CreatePlayer(glm::vec3(float(windowWidth - 100 - 50), 100, 0), scene, 1);



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
		//auto& sceneManager = SceneManager::GetInstance();
		auto& eventManager = EventManager::GetInstance();
		auto& stateManager = GameStateManager::GetInstance();
		auto& inputManager = InputManager::GetInstance();

		bool doContinue = true;
		auto timeLast = chrono::high_resolution_clock::now();

		auto ss = new sdl_sound_system();
		AudioServiceLocator::register_sound_system(ss);

		while (doContinue)
		{
			//Get delta time
			auto timeNow = chrono::high_resolution_clock::now();
			auto deltaTime = timeNow - timeLast;
			doContinue = inputManager.ProcessInput();

			inputManager.HandleInputs();
			stateManager.GetCurrent()->HandleInput();
			stateManager.GetCurrent()->Update(chrono::duration<float>(deltaTime).count());
			AudioServiceLocator::Update();
			renderer.Render();

			stateManager.ProcessStateChange();
			eventManager.ProcessEvents();

			//Update timeLast
			timeLast = timeNow;
		}

		delete ss;
		ss = nullptr;
	}
	Cleanup();
}

void dae::Minigin::CreateHUD(glm::vec3 pos, Scene* scene, int controllerIdx) const
{
	auto HUD = std::make_shared<GameObject>();
	auto player = HUD->AddComponent<Player>();
	auto font = ResourceManager::GetInstance().LoadFont("pixel.otf", 20);


	player->SetControllerIdx(controllerIdx);

		//TEXT COMPONENT
	auto HUDTextCom = HUD->AddComponent<TextComponent>();
	std::string sHUDtext = "LIVES: " + std::to_string(player->GetLives());

	HUDTextCom->SetFont(font);
	HUDTextCom->SetText(sHUDtext);

		//TRANSFORM COMPONENT
	auto sHUDTransformCom = HUD->AddComponent<Transform>();
	sHUDTransformCom->SetPosition(pos);

		//TEXTURE COMPONENT
	HUD->AddComponent<TextureComponent>();

	scene->Add(HUD);

	//CHILD COMPONENT SCORE TEXT
	auto scoreHUD = std::make_shared<GameObject>();
	scoreHUD->SetParent(HUD.get());

		//TEXT COMPONENT
	auto scoreHUDTextCom = scoreHUD->AddComponent<TextComponent>();
	std::string scoreHUDtext = "SCORE: " + std::to_string(player->GetScore());

	scoreHUDTextCom->SetFont(font);
	scoreHUDTextCom->SetText(scoreHUDtext);

		//TRANSFORM COMPONENT
	auto scoreHUDTransformCom = scoreHUD->AddComponent<Transform>();
	scoreHUDTransformCom->SetPosition(pos.x+300,pos.y,pos.z);

		//TEXTURE COMPONENT
	scoreHUD->AddComponent<TextureComponent>();

	scene->Add(scoreHUD);
}

void dae::Minigin::CreatePlayer(glm::vec3 pos, Scene* scene, int controllerIdx) const
{
	const int playerSize = 30;
	auto player = std::make_shared<GameObject>();
	auto spriteCom = player->AddComponent<SpriteComponent>();

	std::string texturePath = "sprites/Player" + std::to_string(controllerIdx + 1) + "WalkingForward.png";

	auto spriteTexture = ResourceManager::GetInstance().LoadTexture(texturePath);
	Sprite sprite{ spriteTexture, 1, 3, 0.5f };
	spriteCom->SetSprite(sprite, playerSize, 0);

	auto transformCom = player->AddComponent<Transform>();
	transformCom->SetPosition(pos);

	auto physics = player->AddComponent<PlayerPhysics>();
	physics->SetControllerIdx(controllerIdx);
	physics->SetDimentions(playerSize, playerSize);

	scene->Add(player);
}
