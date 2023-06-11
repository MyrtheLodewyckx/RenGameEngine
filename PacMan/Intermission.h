#pragma once
#include "Scene.h"


class Intermission1: public dae::Scene
{
	std::shared_ptr<dae::GameObject> m_PacMan{};
	std::shared_ptr<dae::GameObject> m_Ghost{};
	int m_WindWidth{}, m_WindHeight{};
	float m_Timer{};
	bool m_IsHalfway{ false };

public:
	Intermission1() :Scene("Intermission 1") {}
	~Intermission1() override = default;

	virtual void Update(const float deltaTime) override;
	virtual void Initialize() override;
};
