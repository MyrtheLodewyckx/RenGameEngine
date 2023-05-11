#include "SpriteComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "ResourceManager.h"

void dae::SpriteComponent::Update(const float deltaTime)
{
	m_AccuSec += deltaTime;

	if (m_AccuSec > m_Sprite.frameSec)
	{
		// Go to next frame
		++m_ActFrame;
		if (m_ActFrame >= m_Sprite.columns * m_Sprite.rows)
		{
			m_ActFrame = 0;
		}

		// Only keep the remaining time
		m_AccuSec -= m_Sprite.frameSec;
	}
}

void dae::SpriteComponent::Render() const
{
	if (m_Sprite.texturePtr && m_IsRendering)
	{
		const auto pos = m_GameObject->GetGlobalPos();

		float SourceWidth = (float)m_Sprite.texturePtr->GetSize().x / m_Sprite.columns;
		float SourceHeight = (float)m_Sprite.texturePtr->GetSize().y / m_Sprite.rows;

		float sourceX = m_ActFrame % m_Sprite.columns * SourceWidth;
		float sourceY = m_ActFrame % m_Sprite.rows * SourceHeight;

		Renderer::GetInstance().RenderTexture(*m_Sprite.texturePtr, pos.x, pos.y, m_DestWidth, m_DestHeight, sourceX, sourceY, SourceWidth, SourceHeight, m_Flip);
	}
}

void dae::SpriteComponent::SetSprite(Sprite sprite, float width, float height)
{
	m_Sprite = sprite;
	m_Flip = SDL_FLIP_NONE;

	m_DestHeight = height;
	m_DestWidth = width;
}

void dae::SpriteComponent::SetSprite(Sprite sprite, float width, float height, SDL_RendererFlip flip)
{
	SetSprite(sprite, width, height);
	m_Flip = flip;
}

void dae::SpriteComponent::Resize(int width, int height)
{
	m_DestHeight = (float)height;
	m_DestWidth = (float)width;
}

float dae::SpriteComponent::GetWidth() const
{
	return m_DestWidth;
}

float dae::SpriteComponent::GetHeight() const
{
	return m_DestHeight;
}
