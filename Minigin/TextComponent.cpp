#include "TextComponent.h"
#include "font.h"
#include <stdexcept>
#include "GameObject.h"
#include "Renderer.h"
#include "TextureComponent.h"
#include "Texture2D.h"


textComponent::textComponent(dae::GameObject* go)
	:Component(go)
{
}

textComponent::~textComponent()
{
	//delete m_font;
	m_font = nullptr;
}

void textComponent::SetFont(std::shared_ptr<dae::Font> font)
{
	m_font = font;
}

void textComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}

void textComponent::SetColor(SDL_Color color)
{
	m_Color = color;
	m_needsUpdate = true;
}

void textComponent::Update(const float)
{
	if (m_needsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);

		auto textureComp = m_GameObject->GetComponent<TextureComponent>();
		textureComp->SetTexture(std::make_shared<dae::Texture2D>(texture));

		m_needsUpdate = false;
	}
}
