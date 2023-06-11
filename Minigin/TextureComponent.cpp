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
	m_Width = m_texture->GetSize().x;
	m_Height = m_texture->GetSize().y;
}

void TextureComponent::SetTexture(std::shared_ptr<dae::Texture2D> texture)
{
	SetTexture(texture, texture->GetSize().x, texture->GetSize().y);
}

void TextureComponent::SetTexture(const std::string& filename, int width, int height)
{
	m_Width = width;
	m_Height = height;
	m_texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void TextureComponent::SetTexture(std::shared_ptr<dae::Texture2D> texture, int width, int height)
{
	m_Width = width;
	m_Height = height;
	m_texture = texture;
}

glm::vec2 TextureComponent::GetSize()
{
	return { m_Width,m_Height };
}

void TextureComponent::Render() const
{
	auto pos = m_GameObject->GetGlobalPos();
	dae::Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}


