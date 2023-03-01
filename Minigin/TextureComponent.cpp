#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TransformComponent.h"

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

	dae::Renderer::GetInstance().RenderTexture(*m_texture, m_pos.x, m_pos.y);
}

void TextureComponent::Update(const float)
{
	if (m_NeedsUpdate)
	{
		m_pos = m_GameObject->GetComponent<dae::TransformComponent>()->GetPosition();
		m_NeedsUpdate = false;
	}
}


