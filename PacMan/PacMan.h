#pragma once
#include <memory>
#include <vector>

#include "Component.h"
#include "SpriteComponent.h"


class PlayerPhysicsComponent;

namespace dae
{
	class SpriteComponent;
}

class PacMan: public Component
{
	std::shared_ptr<dae::SpriteComponent> m_pSprite{ nullptr };
	dae::Sprite m_SidewaysSprite{};
	dae::Sprite m_VerticalSprite{};
	dae::Sprite m_DyingSprite{};

	float m_Width{}, m_Height{};

	glm::vec3 m_StartPos{};

	inline static int m_PelletsEaten{};
	inline static std::vector<dae::GameObject*> m_PelletsRef{};
	std::vector<dae::GameObject*> m_GhostsRef{};

	void CheckForPellets();
	void CheckForGhosts();
	bool m_MunchSound{};
	float m_Timer{};

	std::shared_ptr<PlayerPhysicsComponent> m_pPhysicsRef{ nullptr };

public:
	PacMan(dae::GameObject* go):Component(go){}
	~PacMan() override;
	void SetDimentions(int width, int height);
	void SetSprites(dae::Sprite sideWays, dae::Sprite vertical, dae::Sprite dying);

	void Update(const float) override;
	void Initialize() override;
	static int GetPelletsEaten();
};
