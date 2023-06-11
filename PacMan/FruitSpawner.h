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
	FruitSpawner(const FruitSpawner& other) = delete;
	FruitSpawner(FruitSpawner&& other) noexcept = delete;
	FruitSpawner& operator=(const FruitSpawner& other) = delete;
	FruitSpawner& operator=(FruitSpawner&& other)	noexcept = delete;

	void Update(const float) override;
};
