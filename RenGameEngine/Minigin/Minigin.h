#pragma once
struct SDL_Window;
namespace dae
{
	class GameObject;
	class Scene;
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};

		void CreateHUD(glm::vec3 pos,Scene &scene, int controllerIdx) const;
		void CreatePlayer(glm::vec3 pos, Scene& scene, int controllerIdx) const;
	};
}