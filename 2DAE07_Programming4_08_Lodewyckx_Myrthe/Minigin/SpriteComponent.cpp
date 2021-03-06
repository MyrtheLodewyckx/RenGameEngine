#include "MiniginPCH.h"
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
	const auto pos = m_Go->GetComponent<Transform>()->GetPosition();
	
	float SourceWidth = m_Sprite.texturePtr->GetWidth()/ m_Sprite.columns;
	float SourceHeight = m_Sprite.texturePtr->GetHeight() / m_Sprite.rows;

	float sourceX = m_ActFrame % m_Sprite.columns * SourceWidth;
	float sourceY = m_ActFrame % m_Sprite.rows * SourceHeight;

	Renderer::GetInstance().RenderTexture(*m_Sprite.texturePtr.get(), pos.x, pos.y, m_DestWidth, m_DestHeight, sourceX, sourceY, SourceWidth,SourceHeight);
}

void dae::SpriteComponent::SetSprite(Sprite sprite, float width, float height)
{
	m_Sprite = sprite;

	if (width == 0 && height == 0)
	{
		m_DestWidth = m_Sprite.texturePtr->GetWidth() / m_Sprite.columns;
		m_DestHeight = m_Sprite.texturePtr->GetHeight() / m_Sprite.rows;
	}
	else if (width == 0)
	{
		m_DestHeight = height;
		m_DestWidth = m_Sprite.texturePtr->GetWidth() / m_Sprite.columns * (height / (m_Sprite.texturePtr->GetHeight() / m_Sprite.rows));
	}
	else if (height == 0)
	{
		m_DestWidth = width;
		m_DestHeight = m_Sprite.texturePtr->GetHeight() / m_Sprite.rows * (width / (m_Sprite.texturePtr->GetWidth() / m_Sprite.columns));
	}
	else
	{
		m_DestHeight = height;
		m_DestWidth = width;
	}
}

float dae::SpriteComponent::GetWidth() const
{
	return m_DestWidth;
}

float dae::SpriteComponent::GetHeight() const
{
	return m_DestHeight;
}
