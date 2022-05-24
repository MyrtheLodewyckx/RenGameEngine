#pragma once
#include "Player.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include <string>

using namespace dae;

class PlayerState
{
public:
	//static WalkingState m_Walking;
	virtual void HandleInput() = 0;
	virtual void Update() = 0;
protected:
	dae::Player m_Player;
	/*dae::Sprite sprites[3]
	{
		{std::string("sprites / Player" + std::to_string(m_Player.GetControllerIdx() + 1) + "WalkingForward.png"),
		1,3,0.5f},
		{std::string("sprites / Player" + std::to_string(m_Player.GetControllerIdx() + 1) + "WalkingSideways.png"),
		1,3,0.5f},
		{std::string("sprites / Player" + std::to_string(m_Player.GetControllerIdx() + 1) + "WalkingSideways.png"),
		1,3,0.5f}
	};*/
};

class WalkingState : public PlayerState
{
	virtual void HandleInput() override;
	virtual void Update() override;
};