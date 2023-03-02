#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

TextureComponent::TextureComponent(dae::GameObject* go)
	:Component(go)
{
}

TextureComponent::~TextureComponent()
{
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void TextureComponent::SetTexture(std::shared_ptr<dae::Texture2D> texture)
{
	m_texture = texture;
}

void TextureComponent::Render() const
{
	auto pos = m_GameObject->GetGlobalPos();
	dae::Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}


