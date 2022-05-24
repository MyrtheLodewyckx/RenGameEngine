#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class Player : public Observer, public Component
	{
		int lives{ 3 };
		unsigned int score{ 0 };

		void IncrementLives();
		void DecrementLives();

		void ChangeScore(int amt);

		virtual void OnNotify(Event event) override;
		virtual void Update(const float deltaTime) override {};

	public:
		int GetLives() const { return lives; };
		int GetScore() const { return score; };
	};
}