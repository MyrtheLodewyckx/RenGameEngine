#pragma once
#include "Command.h"
#include "../PacMan/LevelManager.h"
#include "../PacMan/Physics.h"


namespace dae
{
	class SpriteComponent;
	class LevelManager;
}


class MoveCommand : public Command
{
	int m_DirectionInput{};
	dae::LevelManager* m_pLevelRef{ &dae::LevelManager::GetInstance() };

public:
	int m_Width{};
	int m_Height{};
	MoveCommand(dae::GameObject* go): Command(go) {}
	void Execute(float x, float y, const float deltaTime) override;
	void SetSpeed(float speed);
	int m_AvailableDirection{};
	int* m_CurrentDirection{};
	bool m_IsDying{ false };
};

class MoveUpCommand : public Command
{
	int m_DirectionInput{};
	dae::LevelManager* m_pLevelRef{ &dae::LevelManager::GetInstance() };

public:
	int m_Width{};
	int m_Height{};
	MoveUpCommand(dae::GameObject* go) : Command(go) {}
	void Execute() override;
	void SetSpeed(float speed);
	int m_AvailableDirection{};
	int* m_CurrentDirection{};
	bool m_IsDying{ false };
};

class MoveDownCommand : public Command
{
	int m_DirectionInput{};
	dae::LevelManager* m_pLevelRef{ &dae::LevelManager::GetInstance() };

public:
	int m_Width{};
	int m_Height{};
	MoveDownCommand(dae::GameObject* go) : Command(go) {}
	virtual void Execute() override;
	void SetSpeed(float speed);
	int m_AvailableDirection{};
	int* m_CurrentDirection{};
	bool m_IsDying{ false };
};

class MoveLeftCommand : public Command
{
	int m_DirectionInput{};
	dae::LevelManager* m_pLevelRef{ &dae::LevelManager::GetInstance() };

public:
	int m_Width{};
	int m_Height{};
	MoveLeftCommand(dae::GameObject* go) : Command(go) {}
	void Execute() override;
	void SetSpeed(float speed);
	int m_AvailableDirection{};
	int* m_CurrentDirection{};
	bool m_IsDying{ false };
};

class MoveRightCommand : public Command
{
	int m_DirectionInput{};
	dae::LevelManager* m_pLevelRef{ &dae::LevelManager::GetInstance() };

public:
	int m_Width{};
	int m_Height{};
	MoveRightCommand(dae::GameObject* go) : Command(go) {}
	void Execute() override;
	int m_AvailableDirection{};
	int* m_CurrentDirection{};
	bool m_IsDying{ false };
};

class PlayerPhysicsComponent final : public Physics
{
	MoveCommand* m_pMoveCommand{};
	MoveUpCommand* m_pMoveUpCommand{};
	MoveDownCommand* m_pMoveDownCommand{};
	MoveLeftCommand* m_pMoveLeftCommand{};
	MoveRightCommand* m_pMoveRightCommand{};

public:
	void Update(const float deltaTime) override;
	PlayerPhysicsComponent(dae::GameObject* go);
	~PlayerPhysicsComponent() override;
	void SetController(int playerIdx);
	void SetDimensions(int width,int height) override;
	bool GetIsDying();
	void SetIsDying(bool isDying);

};