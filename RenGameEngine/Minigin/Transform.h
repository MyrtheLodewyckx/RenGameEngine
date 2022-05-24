#pragma once
#include "GameObject.h"
#include "Component.h"

namespace dae
{
	class Transform: public Component
	{
	public:
		Transform(GameObject* go) :Component(go) {}
		virtual void Update(const float) override {}
		virtual void Render() const override {}
		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		void SetPosition(float x, float y, float z);
		void SetPosition(glm::vec3 pos);

	private:
		glm::vec3 m_Position;
		glm::vec3 m_LocalPosition;
	};
}
