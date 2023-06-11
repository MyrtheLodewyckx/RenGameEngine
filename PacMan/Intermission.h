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
	Intermission1(const Intermission1& other) = delete;
	Intermission1(Intermission1&& other) noexcept = delete;
	Intermission1& operator=(const Intermission1& other) = delete;
	Intermission1& operator=(Intermission1&& other)	noexcept = delete;

	virtual void Update(const float deltaTime) override;
	virtual void Initialize() override;
};
