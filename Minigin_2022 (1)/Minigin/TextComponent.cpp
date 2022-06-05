#include "MiniginPCH.h"
#include "TextComponent.h"
#include <SDL_ttf.h>
#include "Font.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Texture2D.h"

void dae::TextComponent::Update(const float)
{
	const SDL_Color color = { 255,255,255 }; // only white text is supported now

	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	auto texturePtr = std::make_shared<Texture2D>(texture);
	m_Go->GetComponent<TextureComponent>()->SetTexture(texturePtr);
	m_NeedsUpdate = false;

}

void dae::TextComponent::Render() const
{
	const auto pos = m_Go->GetComponent<Transform>()->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Go->GetComponent<TextureComponent>()->GetTexture(), pos.x, pos.y);
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetFont(std::shared_ptr<Font> font)
{
	m_Font = font;
}
