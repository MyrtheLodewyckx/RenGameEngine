#pragma once

#include "GhostMovement.h"
#include "../LevelManager.h"




class BlinkyMovement final : public GhostMovement
{
public:
	BlinkyMovement(dae::GameObject* go) : GhostMovement(go) {}
	~BlinkyMovement() override {}
	BlinkyMovement(const BlinkyMovement& other) = delete;
	BlinkyMovement(BlinkyMovement&& other) noexcept = delete;
	BlinkyMovement& operator=(const BlinkyMovement& other) = delete;
	BlinkyMovement& operator=(BlinkyMovement&& other)	noexcept = delete;
	virtual void Update(const float) override;
	virtual void FixedUpdate(const float) override;
};


