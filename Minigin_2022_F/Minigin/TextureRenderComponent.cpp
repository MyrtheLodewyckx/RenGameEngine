#include "MiniginPCH.h"
#include "TextureRenderComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "TransformComponent.h"

void dae::TextureRenderComponent::Render() const
{
	if (!m_TexturePtr.expired())
	{
		//auto pos = m_go.lock()->GetComponent<TransformComponent>().lock()->GetPosition();
		//std::cout << pos.y;
		//Renderer::GetInstance().RenderTexture(*m_TexturePtr.lock().get(), pos.x, pos.y);
	}
}
