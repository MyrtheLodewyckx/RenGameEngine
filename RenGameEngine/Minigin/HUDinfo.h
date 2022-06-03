#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class Transform;

	struct HUDinfo
	{
		int lives = 3;
		int score = 0;
		int pepper = 5;
	};

	class HUD : public Component
	{
		HUDinfo m_Info{};

		int m_PlayerIdx{};

		void IncrementLives();
		void DecrementLives();

		void ChangeScore(int amt);
		void HandleEvents();

		Transform* m_TransformPtr = nullptr;


	public:
		int GetLives() const { return m_Info.lives; };
		int GetScore() const { return m_Info.score; };
		int GetControllerIdx() const { return m_PlayerIdx; };

		virtual void Update(const float) override;
		virtual void Render() const override {};

		void SetPlayerIdx(int idx) { m_PlayerIdx = idx; };

		HUD(GameObject* go) : Component(go) {}
		~HUD() = default;
	};
}