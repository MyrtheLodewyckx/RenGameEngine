#pragma once
#include <memory>

#include "Component.h"
#include "SpriteComponent.h"


class Physics;
class GhostMovement;

class Ghost final : public Component
{
	inline static int m_ScoreValue{ 200 };
	float m_Timer{};
	std::shared_ptr<dae::SpriteComponent> m_pSprite{};
	dae::Sprite m_SidewaysSprite{};
	dae::Sprite m_VerticalSprite{};
	dae::Sprite m_VulnerableSprite{};
	dae::Sprite m_VulnerableEndSprite{};
	std::shared_ptr<Physics> m_pMovementRef{};
	float m_Width, m_Height{};
	bool m_IsVulnerable{ false };

	glm::vec3 m_StartPos{};

	bool m_IsFree{false};

public:
	Ghost(dae::GameObject* go) : Component(go) {}
	~Ghost() = default;
	Ghost(const Ghost& other) = delete;
	Ghost(Ghost&& other) noexcept = delete;
	Ghost& operator=(const Ghost& other) = delete;
	Ghost& operator=(Ghost&& other)	noexcept = delete;
	void SetSprites(dae::Sprite vertical, dae::Sprite sideways);
	void SetDimentions(float width, float height);
	virtual void Initialize() override;
	virtual void Update(const float) override;
	const bool GetIsVulnerable();
	void Eat();
	const int GetScoreValue();
	const void SetFree(bool isFree);
	bool GetIsFree();
};
