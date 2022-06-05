#pragma once
#include "Component.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "Physics.h"



class Player :public dae::Component
{
	static std::vector<Player*> m_ObjectList;

	int m_PlayerIdx{ 0 };
	int m_PepperCharges{ 5 };
	Physics* m_pPhysics{m_Go->GetComponent<Physics>() };
	dae::SpriteComponent* m_pSprite{ m_Go->GetComponent<dae::SpriteComponent>() };
	dae::Sprite m_Sprites[4]
	{};

public:

	int GetPlayerIdx() const { return m_PlayerIdx; };

	static std::vector<Player*> GetAllInstances() { return m_ObjectList; }
	static Player* GetPlayer(int playerIdx) { return m_ObjectList[playerIdx]; }

	SDL_Rect GetHitBox() { if (m_pPhysics)return m_pPhysics->GetHitBox(); else return SDL_Rect(0, 0, 0, 0); }
	glm::vec3 GetPos() { if (m_pPhysics)return m_pPhysics->GetPos(); else return glm::vec3(0, 0, 0); }

	virtual void Update(const float) override;
	virtual void Render() const override {};

	void SetPlayerIdx(int idx);
	void ThrowPepper();


	Player(const Player& other) = delete;
	Player(Player&& other) = delete;
	Player& operator=(const Player& other) = delete;
	Player& operator=(Player&& other) = delete;
	Player(dae::GameObject* go) : Component(go) { m_ObjectList.emplace_back(this); }
	~Player();

};