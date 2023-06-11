#pragma once
#include "Component.h"


namespace dae
{
	class Scene;
}

class FruitSpawner :public Component
{
	int m_NextAmtToBeEated{50};
public:
	FruitSpawner(dae::GameObject* go) :Component(go){}
	~FruitSpawner() override = default;

	void Update(const float) override;
};
