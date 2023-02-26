#pragma once
#include <glm/ext/vector_float3.hpp>

namespace dae
{
	class GameObject;
}

class Component
{
protected:
	dae::GameObject* m_GameObject{ nullptr };
	glm::vec3 m_LocalPosition{};

public:

	Component(dae::GameObject* go) : m_GameObject(go) {}
	virtual ~Component() = default;

	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

	virtual void Update(const float deltaTime);
	virtual void Render() const;
	virtual void FixedUpdate(const float fixedTimeStep);
};