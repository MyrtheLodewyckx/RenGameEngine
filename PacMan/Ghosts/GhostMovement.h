#pragma once
#include <memory>
#include <vector>

#include "Component.h"
#include "../LevelManager.h"
#include "../Physics.h"

namespace dae
{
	class Texture2D;
	class LevelManager;
}

class PacMan;

class GhostMovement: public Physics
{
protected:
	bool m_IsFleeing{};
	std::vector<dae::GameObject*> m_Players{};
	int m_CurrentRow{}, m_CurrentColumn{};
	void SetDirection(glm::vec3 startPos, glm::vec3 target);
	void SetFleeDirection(glm::vec3 startPos, glm::vec3 target);

public:
	GhostMovement(dae::GameObject* go) : Physics(go) {}
	virtual void Initialize() override;
	virtual ~GhostMovement() override = default;
	GhostMovement(const GhostMovement& other) = delete;
	GhostMovement(GhostMovement&& other) noexcept = delete;
	GhostMovement& operator=(const GhostMovement& other) = delete;
	GhostMovement& operator=(GhostMovement&& other)	noexcept = delete;
	void SetFlee(bool isFleeing);
};
