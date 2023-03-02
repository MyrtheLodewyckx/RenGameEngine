#pragma once
#include "Component.h"


class RotateComponent : public Component
{
	float elapsedTime{};
	glm::vec3 m_RotatePoint{};
	bool m_RotateClockWise{true};
	float m_Rad{};
public:
	RotateComponent(dae::GameObject* go): Component(go){}
	void SetRotationPoint(glm::vec3);
	void SetRadius(float rad);
	void RotateClockWise(bool b);
	virtual void Update(const float deltaTime) override;
};