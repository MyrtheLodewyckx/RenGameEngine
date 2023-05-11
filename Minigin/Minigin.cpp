#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
<<<<<<< Updated upstream
=======
#include <chrono>
#include <thread>
#include "Scene.h"
>>>>>>> Stashed changes

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

dae::Minigin::Minigin(const std::string &dataPath, const std::string& windowName)
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
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<dae::Scene* ()>& load)
{
	load();
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

<<<<<<< Updated upstream
	// todo: this update loop could use some work.
=======
	sceneManager.Initialize();

	float fixedTimeStep = 5.f;
	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag = 0.0f;

>>>>>>> Stashed changes
	bool doContinue = true;

	while (doContinue)
	{
<<<<<<< Updated upstream
		doContinue = input.ProcessInput();
		sceneManager.Update();
		renderer.Render();
=======
		auto currentTime = std::chrono::high_resolution_clock::now();
		const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();

		doContinue = input.ProcessInput(deltaTime);

		lag += deltaTime;
		while (lag >= fixedTimeStep)
		{
			sceneManager.FixedUpdate(fixedTimeStep);
			lag -= fixedTimeStep;
		}

		sceneManager.Update(deltaTime);
		renderer.Render();


		//sleep when frame is too fast
		auto sleepTime = fixedTimeStep - deltaTime;
		if (sleepTime > 0)
			std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(sleepTime));

		lastTime = currentTime;
>>>>>>> Stashed changes
	}


}
