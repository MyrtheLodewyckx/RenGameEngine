#pragma once
#include "GameObject.h"
#include "SceneManager.h"


#pragma once
#include "GameState.h"

namespace dae
{
	class GameObject;
	class Scene : public GameState
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object);
		void Remove(std::shared_ptr<GameObject> object);

		void RemoveAll();

<<<<<<< Updated upstream
		void Update();
		void Render() const;
=======
		virtual void Initialize() override;
		virtual void Update(const float deltaTime) override;
		void FixedUpdate(const float fixedTimeStep);
		virtual void Render() const override;
		virtual void HandleInput() override {};

		template<typename t>
		std::vector<std::shared_ptr<GameObject>> GetAllGameObjectsWithComponent();
>>>>>>> Stashed changes

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		std::vector <std::shared_ptr<GameObject>> m_Objects;
		explicit Scene(const std::string& name);

		std::string m_name;
		std::vector < std::shared_ptr<GameObject>> m_objects{};

		static unsigned int m_idCounter;
	};
	template <typename t>
	std::vector<std::shared_ptr<GameObject>> Scene::GetAllGameObjectsWithComponent()
	{
		std::vector<std::shared_ptr<GameObject>> gameObjects{};

		for (const auto& obj : m_objects)
		{
			if (obj->GetComponent<t>())
				gameObjects.emplace_back(obj);
		}

		return gameObjects;
	}
}
