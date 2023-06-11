#pragma once
#include "Component.h"
#include "LevelManager.h"


namespace dae
{
	class LevelManager;
}

class Physics : public Component
{
protected:
	int m_Speed{ 150 };
	int m_WindowWidth{}, m_WindowHeight{};
	int m_Width{}, m_Height{};
	dae::LevelManager* m_pLevelRef{ &dae::LevelManager::GetInstance() };
	int m_CurrentDirection{};
	void Move(float deltaTime);
public:
	Physics(dae::GameObject* go) ;
	~Physics() = default;
	Physics(const Physics& other) = delete;
	Physics(Physics&& other) noexcept = delete;
	Physics& operator=(const Physics& other) = delete;
	Physics& operator=(Physics&& other)	noexcept = delete;
	int GetDirection() const { return m_CurrentDirection; }
	virtual void SetDimensions(int width, int height);
};
