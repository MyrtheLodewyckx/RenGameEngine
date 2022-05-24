#pragma once
#include "Component.h"



namespace dae
{
	class Texture2D;

	struct Sprite
	{
		std::shared_ptr<Texture2D> texturePtr{ nullptr };
		int rows;
		int columns;
		float frameSec;
	};

	class SpriteComponent : public Component
	{
		Sprite m_Sprite;

		float m_AccuSec = 0;
		int   m_ActFrame = 0;

		float m_DestWidth = 0;
		float m_DestHeight = 0;

	public:
		SpriteComponent(GameObject* go) : Component(go) {}
		~SpriteComponent() = default;

		virtual void Update(const float) override;
		virtual void Render() const override;

		void SetSprite(Sprite sprite, float width, float height);

		float GetWidth() const;
		float GetHeight() const;
	
	};
}