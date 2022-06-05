#pragma once
#include <vector>
#include <memory>
#include "Texture2D.h"
#include "SpriteComponent.h"
#include "Transform.h"


enum class MovementDirection
{
	Up,
	Down,
	Left,
	Right,
	None
};

class Physics: public dae::Component
{

protected:
	dae::Transform* m_pTransform = nullptr;
	

	MovementDirection m_Direction = MovementDirection::None;

public:

	bool m_IsOnLadder;
	bool m_IsOnGround;

	Physics(dae::GameObject* go) :Component(go) {}
	virtual ~Physics() {}
	virtual void Update(const float deltaTime) override = 0;
	virtual void Render()const override = 0;
	virtual SDL_Rect GetHitBox() = 0;
	virtual glm::vec3 GetPos() = 0;
	virtual void SetPos(glm::vec3 pos) = 0;
	virtual MovementDirection GetDirection() = 0;
	virtual void HandleMovement(const float deltaTime) = 0;
};