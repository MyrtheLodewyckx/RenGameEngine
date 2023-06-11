#pragma once
#include "Component.h"


class Pellet: public Component
{
public:
	Pellet(dae::GameObject* go) : Component(go){}
	~Pellet() override = default;
	int m_Amt{10};
};
