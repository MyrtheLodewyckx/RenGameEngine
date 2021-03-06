#pragma once
#include "Component.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "Physics.h"

enum class EnemyID
{
	Sausage,
	Pickle,
	Egg
};

class Enemy : public dae::Component
{
	bool m_IsStunned = false;
	bool m_IsFalling = false;
	bool m_IsDead = false;

	void HandlePlayerCollision();
	void HandleStun(const float deltaTime);
	void HandleDeath(const float deltaTime);

	float m_Timer = 0;

	static std::vector<Enemy*> m_ObjectList;
	Physics* m_pPhysics{};

	glm::vec3 m_SpawnPoint{};

	EnemyID m_ID;

	dae::SpriteComponent* m_pSprite{};
	dae::Sprite m_Sprites[4]
	{};

public:
	void SetIsStunned(bool b) { m_IsStunned = b; }
	void SetIsFalling(bool b) { m_IsFalling = b; std::cout << "Falling\n"; }
	bool GetIsFalling() { return m_IsFalling; }

	static std::vector<Enemy*> GetAllInstances() { return m_ObjectList; }

	SDL_Rect GetHitBox() {
		if (!m_pPhysics)
			m_pPhysics = m_Go->GetComponent<Physics>(); return m_pPhysics->GetHitBox(); }
	glm::vec3 GetPos() {
		if (!m_pPhysics)
			m_pPhysics = m_Go->GetComponent<Physics>(); return m_pPhysics->GetPos(); }

	void SetPos(glm::vec3 pos) {
		if (m_pPhysics)
			m_pPhysics->SetPos(pos);
	}

	virtual void Update(const float) override;
	virtual void Render() const override {};

	void SetEnemyID(EnemyID id);

	void Die();

	Enemy(const Enemy& other) = delete;
	Enemy(Enemy&& other) = delete;
	Enemy& operator=(const Enemy& other) = delete;
	Enemy& operator=(Enemy&& other) = delete;
	Enemy(dae::GameObject* go) : Component(go) { m_ObjectList.emplace_back(this); }
	~Enemy();

};