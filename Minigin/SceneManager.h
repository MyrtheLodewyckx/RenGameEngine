#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

<<<<<<< Updated upstream
		void Update();
=======
		std::shared_ptr<Scene> GetCurrentScene() { return m_scenes[int(m_scenes.size() - 1)]; }

		void Initialize();
		void Update(const float deltaTime);
		void FixedUpdate(const float fixedTimeStep);
>>>>>>> Stashed changes
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
	};
}
