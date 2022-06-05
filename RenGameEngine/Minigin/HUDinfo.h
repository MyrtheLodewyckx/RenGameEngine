#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class Transform;

	class HUD : public Component
	{
		int m_PlayerIdx{};
		int m_Pepper = 5;

		void IncrementLives();
		void DecrementLives();

		void ChangeScore(int amt);
		void HandleEvents();

		Transform* m_TransformPtr = nullptr;


	public:
		int GetControllerIdx() const { return m_PlayerIdx; };

		virtual void Update(const float) override;
		virtual void Render() const override {};

		void SetPlayerIdx(int idx) { m_PlayerIdx = idx; };

		HUD(GameObject* go) : Component(go) {}
		~HUD() = default;
	};
}