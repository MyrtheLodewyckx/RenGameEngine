#include "FPSComp.h"
#include "GameObject.h"
#include "TextComp.h"

FPSComponent::FPSComponent(dae::GameObject* go)
	:Component(go)
{
}

FPSComponent::~FPSComponent()
{
}

void FPSComponent::Update(const float deltaTime)
{
	if (m_NeedsUpdate)
	{
		m_txtComp = m_GameObject->GetComponent<textComponent>();
		m_NeedsUpdate = false;
	}

	m_counter += deltaTime;
	++m_Frames;

	if (m_counter > 1)
	{
		std::string str = std::to_string(m_Frames) + " FPS";
		m_txtComp->SetText(str);
		m_counter = 0;
		m_Frames = 0;
	}

}

void FPSComponent::FixedUpdate(const float)
{
}

void FPSComponent::Render() const
{
}
