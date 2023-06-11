#pragma once
#include "Component.h"


class Pellet: public Component
{
public:
	Pellet(dae::GameObject* go) : Component(go){}
	~Pellet() override = default;
	Pellet(const Pellet& other) = delete;
	Pellet(Pellet&& other) noexcept = delete;
	Pellet& operator=(const Pellet& other) = delete;
	Pellet& operator=(Pellet&& other)	noexcept = delete;
	int m_Amt{10};
};
