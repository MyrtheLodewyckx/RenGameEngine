#pragma once
#include <vector>

#include "GameObject.h"

#include "SceneManager.h"


#pragma once

namespace dae
{
	class GameObject;
	class Scene
	{
	public:

		void Add(const std::shared_ptr<GameObject>& object);
		void RemoveAll();

		virtual void Initialize();
		virtual void Update(const float deltaTime);
		void FixedUpdate(const float fixedTimeStep);
		virtual void Render() const;
		virtual void PostRender() const;
		template<typename t>
		std::vector<GameObject*> GetAllGameObjectsWithComponent();

		virtual void Pause() {}
		virtual void Start() {}

		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		explicit Scene(const std::string& name);
	private:

		std::string m_name;
		std::vector < std::shared_ptr<GameObject>> m_objects{};

		void Remove(std::shared_ptr<GameObject> object);

		static unsigned int m_idCounter;
	};
	template <typename t>
	std::vector<GameObject*> Scene::GetAllGameObjectsWithComponent()
	{
		std::vector<GameObject*> gameObjects{};

		for (const auto& obj : m_objects)
		{
			if (obj->GetComponent<t>())
				gameObjects.emplace_back(obj.get());
		}

		return gameObjects;
	}
}
