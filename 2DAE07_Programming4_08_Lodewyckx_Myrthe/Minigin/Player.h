#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class Player : public Component
	{
		int lives{ 3 };
		unsigned int score{ 0 };

		int m_ControllerIdx{ 0 };

		void IncrementLives();
		void DecrementLives();

		void ChangeScore(int amt);

		//virtual void OnNotify(Event event) override;
	
		void HandleEvents();


	public:
		int GetLives() const { return lives; };
		int GetScore() const { return score; };
		int GetControllerIdx() const { return m_ControllerIdx; };

		virtual void Update(const float) override;
		virtual void Render() const override {};

		void SetControllerIdx(int idx) { m_ControllerIdx = idx; };

		Player(GameObject* go) : Component(go) {}
		~Player() = default;
	};
}