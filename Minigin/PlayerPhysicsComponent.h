#pragma once
#include "Command.h"
#include "Component.h"


class MoveCommand : public Command
{
	float m_Speed{ 30.f };

public:
	MoveCommand(dae::GameObject* go): Command(go) {}
	void Execute(float x, float y, const float deltaTime) override;
	void SetSpeed(float speed);
};

class PlayerPhysicsComponent final : public Component
{
public:
	PlayerPhysicsComponent(dae::GameObject* go);
	~PlayerPhysicsComponent() override = default;
};