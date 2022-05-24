#pragma once
#include "Component.h"

namespace dae
{
	class FPSComponent : public Component
	{

	public:
		virtual void Update(const float) override {};
		virtual void Render() const override {};

		FPSComponent(std::weak_ptr<GameObject> go)
			:Component(go)
		{}
		~FPSComponent() {};
	};
}