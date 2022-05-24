#pragma once
#include "Component.h"
#include "Exceptions.h"

namespace dae
{
	class Texture2D;
	class GameObject final
	{
	public:
		void Update(const float deltaTime);
		void Render() const;

		GameObject();
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		
		Component* AddComponent(const Component& component)
		{
			auto c = std::make_shared<Component>(component);
			m_Components.push_back(c);
		}

		template <typename ComponentType>
		std::weak_ptr<ComponentType> GetComponent() const
		{
			for (const auto& component : m_Components)
				if (const auto result = std::dynamic_pointer_cast<ComponentType>(component); result != nullptr)
					return result;

			return std::weak_ptr<ComponentType>();
		}

		void SetParent(GameObject* parent);

		decltype(auto) GetParent();

		size_t GetChildCount() const;

		decltype(auto) GetChildAt(int idx) const;

		void RemoveChild(int idx);
		void AddChild(GameObject* child);


	private:

		GameObject* m_Parent{nullptr};
		std::vector<GameObject*> m_Children{};
		std::vector<std::shared_ptr<Component>> m_Components{};
	};

	
}
