#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Rengen.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <chrono>
#include <thread>

#include "EventManager.h"
#include "Scene.h"
#include "SoundSystem.h"

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::Rengen::Rengen(const std::string &dataPath, const std::string& windowName, int windowWidth, int windowHeight)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		windowName.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth,
		windowHeight,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

dae::Rengen::~Rengen()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Rengen::Run(const std::function<dae::Scene* ()>& load)
{
	load();

	// Init 
	auto& eventManager = EventManager::GetInstance();
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();


	auto ss = std::make_shared<sdl_sound_system>();
	AudioServiceLocator::register_sound_system(ss.get());

	sceneManager.Initialize();

	using clock = std::chrono::steady_clock;
	double fixedDt = 1.0 / 120.0;

	double targetFrame = 1.0 / 144.0;

	auto lastTime = clock::now();
	double lag = 0.0;

	bool doContinue = true;
	while (doContinue)
	{
		const auto currentTime = clock::now();
		double frameSec = std::chrono::duration<double>(currentTime - lastTime).count();

		if (frameSec > 0.25) frameSec = 0.25;

		lag += frameSec;

		doContinue = input.ProcessInput(static_cast<float>(frameSec));
		sceneManager.ProcessStateChange();

		while (lag >= fixedDt)
		{
			sceneManager.FixedUpdate(static_cast<float>(fixedDt));
			lag -= fixedDt;
		}

		sceneManager.Update(static_cast<float>(frameSec));
		AudioServiceLocator::Update();
		renderer.Render();

		if (targetFrame > 0.0)
		{
			const auto frameElapsed = std::chrono::duration<double>(clock::now() - currentTime).count();
			const double remaining = targetFrame - frameElapsed;
			if (remaining > 0.0)
				std::this_thread::sleep_for(std::chrono::duration<double>(remaining));
		}

		eventManager.ProcessEvents();
		lastTime = currentTime;
	}
}
