#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "Renderer.h"
#include "Transform.h"

void dae::TextureComponent::Render() const
{
	if (!m_IsAlreadyRendered)
	{
		const auto pos = m_Go->GetComponent<Transform>()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_TexturePtr.get(), pos.x, pos.y);
	}
}
