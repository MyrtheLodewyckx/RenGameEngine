#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include <memory>

class Component;

namespace dae
{

	class GameObject final
	{
	public:
		void Update(const float deltaTime);
		void Render() const;

		GameObject() {};
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template<typename ComponentType>
		ComponentType* GetComponent() const
		{
			for (std::shared_ptr<Component> c : m_Components)
			{
				std::shared_ptr<ComponentType> result = std::dynamic_pointer_cast<ComponentType>(c);
				if (result != nullptr)
					return result.get();
			}

			return nullptr;
		}

		template<typename ComponentType>
		ComponentType* AddComponent()
		{
			auto c = std::make_shared<ComponentType>(this);

			auto component = std::dynamic_pointer_cast<Component>(c);
			m_Components.push_back(component);

			return c.get();
		}

		template <typename T> void RemoveComponent()
		{
		}

		void SetParent(GameObject* parent);

		GameObject* GetParent() { return m_Parent; };

		size_t GetChildCount() const;

		decltype(auto) GetChildAt(int idx) const;

	private:
		std::vector< std::shared_ptr<Component>> m_Components{};
		GameObject* m_Parent {nullptr};
		std::vector<GameObject*> m_Children{};
	};
}
