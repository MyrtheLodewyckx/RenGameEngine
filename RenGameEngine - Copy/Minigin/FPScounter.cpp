#include "MiniginPCH.h"
#include "FPScounter.h"
#include "TextComponent.h"
#include "GameObject.h"

void dae::FPSCounter::Update(const float deltaTime)
{
	m_counter += deltaTime;
	++m_Frames; 

	if (m_counter > 1)
	{
		std::string str = std::to_string(m_Frames) + " FPS";
		m_Go->GetComponent<TextComponent>()->SetText(str);
		m_counter = 0;
		m_Frames = 0;
	}
}
