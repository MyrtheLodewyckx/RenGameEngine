#pragma once

#include "GhostMovement.h"
#include "../LevelManager.h"




class BlinkyMovement final : public GhostMovement
{
public:
	BlinkyMovement(dae::GameObject* go) : GhostMovement(go) {}
	~BlinkyMovement() override {}
	virtual void Update(const float) override;
	virtual void FixedUpdate(const float) override;
};


