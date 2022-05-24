//#pragma once
//#include "Player.h"
//#include "SpriteComponent.h"
//#include "ResourceManager.h"
//#include <string>
//
//using namespace dae;
//
//class PlayerState
//{
//	int m_PlayerIdx;
//public:
//	PlayerState();
//	virtual void HandleInput() = 0;
//	virtual void Update() = 0;
//	void SetPlayerIdx(int playerIdx);
//	std::shared_ptr<Texture2D> m_pWalkingTexture{nullptr};
//	std::shared_ptr<Texture2D> m_pClimbingDownTexture{ nullptr };
//	std::shared_ptr<Texture2D> m_pClimbingUpTexture{ nullptr };
//
//protected:
//	dae::Sprite sprites[3]
//	{
//		{m_pClimbingDownTexture,1,3,0.5f},
//		{m_pWalkingTexture,1,3,0.5f},
//		{m_pClimbingUpTexture,1,3,0.5f}
//	};
//};
//
//class WalkingState: public PlayerState
//{
//public:
//	WalkingState() = default;
//	virtual void HandleInput() override {};
//	virtual void Update() override {};
//};