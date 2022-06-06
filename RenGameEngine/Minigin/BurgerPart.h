#pragma once
#include "Component.h"
#include <vector>

namespace dae
{
	class TextureComponent;
	class Transform;
	class GameObject;
	class BurgerPart : public Component
	{
		static std::vector<BurgerPart*> m_ObjectList;
		std::vector<int> m_EnterPoints{};
		int m_Height,m_Width = 0;
		void Fall(const float deltaTime);
		Transform* m_TransformPtr = nullptr;
		TextureComponent* m_texturePtr = nullptr;
		bool m_IsFalling = false;
		bool m_IsOnPlate = false;
		void CheckWinCondition();
		void CheckIsEnemyOn();
		std::vector<int> m_EnemiesFallingWith{};
	public:
		BurgerPart(const BurgerPart& other) = delete;
		BurgerPart(BurgerPart&& other) = delete;
		BurgerPart& operator=(const BurgerPart& other) = delete;
		BurgerPart& operator=(BurgerPart&& other) = delete;
		BurgerPart(GameObject* go);
		~BurgerPart();
		virtual void Update(const float deltaTime) override;
		virtual void Render() const override;
		void SetDimentions(int width, int height);

	};
}