#pragma once
#include <memory>
#include <glm/ext/vector_float3.hpp>

namespace dae
{
	class GameObject;
}

class Component
{
	bool m_IsMarkedForDeletion{ false };

protected:
	dae::GameObject* m_GameObject{ nullptr };

public:

	bool GetIsMarkedForDeletion() { return m_IsMarkedForDeletion; }
	void SetIsMarkedForDeletion(bool b) { m_IsMarkedForDeletion = b; }

	Component(dae::GameObject* go) : m_GameObject(go) {}
	virtual ~Component() = default;

	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

	virtual void Initialize(){}
	virtual void Update(const float) {}
	virtual void Render() const {}
	virtual void PostRender() const {}
	virtual void FixedUpdate(const float){}
};