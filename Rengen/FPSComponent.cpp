#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

FPSComponent::FPSComponent(dae::GameObject* go)
	:Component(go)
{
}

FPSComponent::~FPSComponent()
{
}

void FPSComponent::Update(const float deltaTime)
{
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

void FPSComponent::Initialize()
{
	m_txtComp = m_GameObject->GetComponent<textComponent>();
}

