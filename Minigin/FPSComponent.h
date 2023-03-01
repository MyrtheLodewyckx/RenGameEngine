#pragma once
#include "Component.h"

class textComponent;

class FPSComponent: public Component
{
	int m_Frames = 0;
	float m_counter = 0;
	textComponent* m_txtComp{nullptr};
	bool m_NeedsUpdate{ true };
public:
	FPSComponent(dae::GameObject* go);
	~FPSComponent();

	virtual void Update(const float deltaTime) override;
};