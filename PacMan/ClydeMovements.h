#pragma once

#include "Ghosts/GhostMovement.h"




class ClydeMovement final : public GhostMovement
{
	float m_Timer{};
public:
	ClydeMovement(dae::GameObject* go) : GhostMovement(go) {}
	~ClydeMovement() override {}
	virtual void Update(const float) override;
	virtual void FixedUpdate(const float) override;
};


