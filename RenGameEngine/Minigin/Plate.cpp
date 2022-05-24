#include "MiniginPCH.h"
#include "Plate.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Renderer.h"

std::vector<dae::Plate*> dae::Plate::m_ObjectList;


void dae::Plate::Update(const float)
{
	if (!m_pTexture)
		m_pTexture = m_Go->GetComponent<TextureComponent>();
}

void dae::Plate::Render() const
{
	Renderer::GetInstance().RenderTexture(*m_pTexture->GetTexture().get(), (float)m_HitBox.x, (float)m_HitBox.y, (float)m_HitBox.w, (float)m_HitBox.h);
}

void dae::Plate::SetDimentions(int width, int height)
{
	m_HitBox.x = (int)m_Go->GetComponent<Transform>()->GetPosition().x;
	m_HitBox.y = (int)m_Go->GetComponent<Transform>()->GetPosition().y;
	m_HitBox.w = width;
	m_HitBox.h = height;
}

dae::Plate::Plate(GameObject* go)
	:Component(go)
{
	m_ObjectList.emplace_back(this);
}
