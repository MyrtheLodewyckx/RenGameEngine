#pragma once
#include <string>
#include <memory>
#include "Singleton.h"
#include <stack>
#include "Scene.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{

		std::stack<std::shared_ptr<Scene>> m_scenes {};
		std::unique_ptr<Scene> m_newState {};
		bool m_IsPaused = false;
		friend class Singleton<SceneManager>;

		bool m_add = false;
		bool m_replace = false;
		bool m_remove = false;

	public:
		Scene& CreateScene(const std::string& name);

		std::shared_ptr<Scene> GetCurrentScene() { return m_scenes.top(); }

		void Initialize();
		void Update(const float deltaTime);
		void FixedUpdate(const float fixedTimeStep);
		void Render();
		void PostRender() const;

		void Add(std::unique_ptr<Scene> toAdd, bool replace = false);
		void PopCurrent();
		void ProcessStateChange();
		std::unique_ptr<Scene>& GetCurrent();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
	};
}
