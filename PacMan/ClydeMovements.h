#pragma once

#include "Ghosts/GhostMovement.h"




class ClydeMovement final : public GhostMovement
{
	float m_Timer{};
public:
	ClydeMovement(dae::GameObject* go) : GhostMovement(go) {}
	~ClydeMovement() override {}
	ClydeMovement(const ClydeMovement& other) = delete;
	ClydeMovement(ClydeMovement&& other) noexcept = delete;
	ClydeMovement& operator=(const ClydeMovement& other) = delete;
	ClydeMovement& operator=(ClydeMovement&& other)	noexcept = delete;
	virtual void Update(const float) override;
	virtual void FixedUpdate(const float) override;
};


