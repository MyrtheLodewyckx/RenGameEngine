#pragma once
#include <memory>
#include "Component.h"

class textComponent;

class FPSComponent: public Component
{
	int m_Frames = 0;
	float m_counter = 0;
	std::shared_ptr<textComponent> m_txtComp{nullptr};

public:
	FPSComponent(dae::GameObject* go);
	~FPSComponent();
	FPSComponent(const FPSComponent& other) = delete;
	FPSComponent(FPSComponent&& other) noexcept = delete;
	FPSComponent& operator=(const FPSComponent& other) = delete;
	FPSComponent& operator=(FPSComponent&& other)	noexcept = delete;

	virtual void Update(const float deltaTime) override;
	virtual void Initialize() override;
};