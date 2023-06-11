#pragma once
#include <memory>
#include "Component.h"
#include <list>

namespace dae
{
	class GameObject final
	{
	public:

		void Initialize();
		void Update(const float deltaTime);
		void FixedUpdate(const float fixedTimeStep);
		void PostRender() const;
		void Render() const;

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
		void SetParent(std::shared_ptr<GameObject> go);
		void SetPosition(float x, float y, float z);
		void SetPosition(glm::vec3 pos);
		glm::vec3 GetGlobalPos();

		void remove();
		bool GetIsMarkedForDeletion();

		//COMPONENTS
		template <typename T> std::shared_ptr<T> AddComponent() 
		{
			std::shared_ptr<T> comp = std::make_shared<T>(this);
			m_Components.push_back(std::dynamic_pointer_cast<Component>(comp));
			return comp;
		}

		template <typename T> std::shared_ptr<T> GetComponent()
		{
			for (auto c : m_Components)
			{
				std::shared_ptr<T> result = std::dynamic_pointer_cast<T>(c);
				if (result != nullptr)
					return result;
			}

			return nullptr;
		}

		template <typename T> void RemoveComponent()
		{
			for (auto c : m_Components)
			{
				std::shared_ptr<T> result = dynamic_cast<std::shared_ptr<T>>(c);
				if (result != nullptr)
				{
					c->SetIsMarkedForDeletion(true);
				}
			}
		}
		

	private:
		glm::vec3 m_GlobalPosition{};
		glm::vec3 m_LocalPosition{};

		bool m_GlobalPosFlag{false};
		
		std::list<std::shared_ptr<Component>> m_Components{};
		std::list<GameObject*> m_Children{};
		std::shared_ptr<GameObject> m_Parent{};

		bool m_IsMarkedForDeletion{false};
	};
}
