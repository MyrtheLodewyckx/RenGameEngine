#pragma once
#include "Component.h"
#include <memory>
#include <SDL_render.h>

namespace dae
{
	class Texture2D;

	struct Sprite
	{
		std::shared_ptr<Texture2D> texturePtr{ nullptr };
		int rows = 0;
		int columns = 0;
		float frameSec = 0;
	};

	class SpriteComponent : public Component
	{
		Sprite m_Sprite;

		float m_AccuSec = 0;
		int   m_ActFrame = 0;

		float m_DestWidth = 0;
		float m_DestHeight = 0;
		SDL_RendererFlip m_Flip = (SDL_RendererFlip)0;

		

	public:
		bool m_IsRendering = true;
		SpriteComponent(GameObject* go) : Component(go) {}
		~SpriteComponent() = default;

		virtual void Update(const float) override;
		virtual void Render() const override;

		void SetSprite(Sprite sprite, float width, float height);
		void SetSprite(Sprite sprite, float width, float height, SDL_RendererFlip);

		void Resize(int width, int height);

		float GetWidth() const;
		float GetHeight() const;
	
	};
}
