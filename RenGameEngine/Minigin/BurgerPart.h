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

	public:
		BurgerPart(GameObject* go);
		~BurgerPart();
		virtual void Update(const float deltaTime) override;
		virtual void Render() const override;
		void SetDimentions(int width, int height);

	};
}