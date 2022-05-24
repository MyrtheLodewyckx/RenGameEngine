#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class FPSCounter : public Component
	{
		int m_Frames = 0;
		float m_counter = 0;
	public:
		virtual void Update(const float) override;
		virtual void Render() const override {};

		FPSCounter(GameObject* go) : Component(go) {}
		~FPSCounter() = default;
	};
}