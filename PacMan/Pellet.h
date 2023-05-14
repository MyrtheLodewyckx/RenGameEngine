#pragma once
#include "Component.h"


class Pellet final : public Component
{
public:
	Pellet(dae::GameObject* go) : Component(go){}
	~Pellet() = default;
	int m_Amt{10};
};
