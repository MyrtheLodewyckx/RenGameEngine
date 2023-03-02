#pragma once
#include <memory>
#include "Component.h"
#include <list>

namespace dae
{
	class GameObject final
	{
	public:
		virtual void Update(const float deltaTime);
		virtual void FixedUpdate(const float fixedTimeStep);
		virtual void Render() const;

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
		void SetParent(std::shared_ptr<GameObject> go);
		void SetPosition(float x, float y, float z);
		glm::vec3 GetGlobalPos();


		//COMPONENTS
		template <typename T> T* AddComponent() 
		{
			T* comp = new T(this);
			m_Components.push_back(dynamic_cast<Component*>(comp));

			return comp;
		}

		template <typename T> T* GetComponent()
		{
			for (Component* c : m_Components)
			{
				T* result = dynamic_cast<T*>(c);
				if (result != nullptr)
					return result;
			}

			return nullptr;
		}

		template <typename T> void RemoveComponent()
		{
			for (std::shared_ptr<Component> c : m_Components)
			{
				T* result = dynamic_cast<T*>(c);
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

		std::list<Component*> m_Components{};
		std::list<GameObject*> m_Children{};
		std::shared_ptr<GameObject> m_Parent{};
	};
}
