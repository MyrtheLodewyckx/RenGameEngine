#pragma once
#pragma once


#include "Ghosts/GhostMovement.h"


class InkyMovement final : public GhostMovement
{
	std::vector<Physics*> m_PacManPhysics{};
public:
	InkyMovement(dae::GameObject* go) : GhostMovement(go) {}
	~InkyMovement() override {}
	virtual void Update(const float) override;
	virtual void FixedUpdate(const float) override;
	void Initialize() override;
};


