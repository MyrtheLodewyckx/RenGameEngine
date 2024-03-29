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
		SpriteComponent(dae::GameObject* go) : Component(go) {}
		~SpriteComponent() = default;
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) noexcept = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other)	noexcept = delete;

		virtual void Update(const float) override;
		virtual void Render() const override;

		void SetSprite(Sprite sprite, float width, float height);
		void SetSprite(Sprite sprite, float width, float height, SDL_RendererFlip);
		void SetRowsCols(int rows, int cols);
		void Resize(int width, int height);

		float GetWidth() const;
		float GetHeight() const;

		void Reset();

		float GetSpriteTime();
	
	};
}
