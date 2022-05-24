#pragma once
#include "Component.h"

namespace dae
{
	class TransformComponent final: public Component
	{
	public:
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);

		virtual void Update(const float) override {};
		virtual void Render() const override {};

		TransformComponent(std::weak_ptr<GameObject> go)
			:Component(go)
		{}

		virtual ~TransformComponent() override {};
	private:
		glm::vec3 m_Position;
	};
}
