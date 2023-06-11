#pragma once
#include <vector>

#include "Component.h"
#include "Ghosts/Ghost.h"


class EnemyManager: public Component
{
	float m_Timer{};
	std::vector<dae::GameObject*> m_GhostsObj{};
	std::vector<Ghost*> m_Ghosts{};
	glm::vec3 m_SpawnPos{};

public:
	EnemyManager(dae::GameObject* go);
	~EnemyManager() override = default;

	virtual void Update(const float) override;
	void Initialize() override;
	void SetSpawnPosition(glm::vec3 pos);
};
