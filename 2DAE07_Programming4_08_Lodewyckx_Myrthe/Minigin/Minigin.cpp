#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "XInputManager.h"
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
#include <steam_api.h>
#include "Achivements.h"
#include "FPScounter.h"
#include "Audio.h"

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
	int windowWidth{};
	int windowHeight{};
	SDL_GetWindowSize(m_Window, &windowWidth, &windowHeight);

	//ADD INSTRUCTIONS TO CONSOLE
	std::cout << "----HOW TO PLAY----\n";
	std::cout << "PRESS A TO SING\n";
	std::cout << "PRESS B TO JUMP\n";
	std::cout << "PRESS Y TO DANCE AND GAIN POINTS\n";
	std::cout << "PRESS X TO DIE\n";

	auto backgroundParent = std::make_shared<GameObject>();

	//ADD BACKGROUND
	auto background = std::make_shared<GameObject>();
	background->SetParent(backgroundParent.get());

	auto texture = ResourceManager::GetInstance().LoadTexture("background.jpg");
	auto textureCom = background->AddComponent<TextureComponent>();
	textureCom->SetTexture(texture);

	auto transformCom = background->AddComponent<Transform>();
	transformCom->SetPosition(0, 0, 0);

	scene.Add(background);

	//ADD LOGO
	auto logo = std::make_shared<GameObject>();
	logo->SetParent(backgroundParent.get());

	auto logoTexture = ResourceManager::GetInstance().LoadTexture("logo.png");
	auto logoTextureComponent = logo->AddComponent<TextureComponent>();
	logoTextureComponent->SetTexture(logoTexture);

	auto logoTransformComponent = logo->AddComponent<Transform>();
	logoTransformComponent->SetPosition(216, 180, 0);

	scene.Add(logo);

	//ADD TEXT
	auto text = std::make_shared<GameObject>();
	text->SetParent(backgroundParent.get());

	auto textComponent = text->AddComponent<TextComponent>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	textComponent->SetFont(font);
	textComponent->SetText("Programming 4 Assignment");

	text->AddComponent<TextureComponent>();

	auto textTransformCom = text->AddComponent<Transform>();
	textTransformCom->SetPosition(80, 20, 0);
	scene.Add(text);

	//ADD FPS COUNTER
	auto fps = std::make_shared<GameObject>();

	auto fpsText = fps->AddComponent<TextComponent>();
	fpsText->SetFont(font);
	fpsText->SetText("0 FPS");

	fps->AddComponent<TextureComponent>();

	auto fpsPos = fps->AddComponent<Transform>();
	fpsPos->SetPosition(10, 50, 0);

	fps->AddComponent<FPSCounter>();

	scene.Add(fps);

	//ADD PETER PEPPER HUD
	CreateHUD(glm::vec3(20, 200, 0), scene, 0);

	//ADD PETER PEPPER
	CreatePlayer(glm::vec3(100, 100, 0), scene, 0);

	//ADD SALLY SALT HUD
	CreateHUD(glm::vec3((float)windowWidth - 170, 200, 0), scene, 1);

	//ADD SALLY SALT
	CreatePlayer(glm::vec3(float(windowWidth - 100 - 50), 100, 0), scene, 1);

}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SteamAchievements::GetInstance().Destroy();
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
		auto& eventManager = dae::EventManager::GetInstance();
		auto inputPtr = new XInputManager(0);
		bool doContinue = true;
		auto timeLast = chrono::high_resolution_clock::now();
		auto ss = new sdl_sound_system();
		ServiceLocator::register_sound_system(ss);

		while (doContinue)
		{
			//Get delta time
			auto timeNow = chrono::high_resolution_clock::now();
			auto deltaTime = timeNow - timeLast;
			doContinue = inputPtr->ProcessInput();

			inputPtr->HandleInputs();
			sceneManager.Update(chrono::duration<float>(deltaTime).count());
			ServiceLocator::Update();
			renderer.Render();

			eventManager.ProcessEvents();
			SteamAPI_RunCallbacks();
			//Update timeLast
			timeLast = timeNow;
		}
		delete inputPtr;
		delete ss;
		inputPtr = nullptr;
		ss = nullptr;
	}
	Cleanup();
}

void dae::Minigin::CreateHUD(glm::vec3 pos, Scene &scene, int controllerIdx) const
{
	auto HUD = std::make_shared<GameObject>();
	auto player = HUD->AddComponent<Player>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);


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

	scene.Add(HUD);

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
	scoreHUDTransformCom->SetPosition(pos.x,pos.y+50,pos.z);

		//TEXTURE COMPONENT
	scoreHUD->AddComponent<TextureComponent>();

	scene.Add(scoreHUD);
}

void dae::Minigin::CreatePlayer(glm::vec3 pos, Scene& scene, int controllerIdx) const
{
	auto player = std::make_shared<GameObject>();
	auto spriteCom = player->AddComponent<SpriteComponent>();

	std::string texturePath = "sprites/Player" + std::to_string(controllerIdx + 1) + "WalkingForward.png";

	auto spriteTexture = ResourceManager::GetInstance().LoadTexture(texturePath);
	Sprite sprite{ spriteTexture, 1, 3, 0.5f };
	spriteCom->SetSprite(sprite, 80, 0);

	auto transformCom = player->AddComponent<Transform>();
	transformCom->SetPosition(pos);

	scene.Add(player);
}
