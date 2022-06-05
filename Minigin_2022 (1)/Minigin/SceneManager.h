#pragma once
#include "Singleton.h"
#include "GameState.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>, public GameState
	{
	public:
		Scene& CreateScene(const std::string& name);

		virtual void Update(const float deltaTime) override;
		virtual void Render()const override;
		void Init() override {};
		void HandleInput() override {};

	private:
		bool m_IsPaused = false;
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
