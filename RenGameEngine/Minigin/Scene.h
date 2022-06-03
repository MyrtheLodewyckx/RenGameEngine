#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene: public GameState
	{
	public:
		void Add(const std::shared_ptr<GameObject>& object);

		virtual void Update(const float deltaTime) override;
		virtual void Render() const override;
		virtual void HandleInput() override {};
		virtual void Init() override {};

		Scene(int lvl);
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		std::vector <std::shared_ptr<GameObject>> m_Objects;
		int m_Level = 1;
	};

}
