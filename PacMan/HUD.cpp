#include "HUD.h"

#include <utility>
#include <glm/vec2.hpp>

#include "EventManager.h"
#include "GameObject.h"
#include "PacManEvents.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

HUD::HUD(dae::GameObject* go)
	:Component(go)
{
	m_pPacMan_Icon = dae::ResourceManager::GetInstance().LoadTexture("PacMan_Icon.png");
	m_pRendererRef = &dae::Renderer::GetInstance();
}


void HUD::Update(const float)
{
	auto e = dae::EventManager::GetEvent();

	if (e == nullptr)
		return;

	switch (e->ID)
	{
	case (int)PacManEvents::SCORE_CHANGE:
	{
		auto p = dynamic_cast<SCORE_CHANGE*>(e);
		gScore += p->amt;
		m_pScoreText->SetText("Score:" + std::to_string(gScore));
		break;
	}
	case (int)PacManEvents::LIVES_CHANGE:
	{
		auto l = dynamic_cast<LIVES_CHANGE*>(e);
		m_Lives += l->amt;
			if(m_Lives == 0)
			{
				auto loseEvent = new LOSE();
				dae::EventManager::GetInstance().AddEvent(loseEvent);
			}
		break;
	}
	}
}

void HUD::Render() const
{
	int offset{10};

	int windowWidth{};
	int windowHeight{};
	SDL_GetWindowSize(m_pRendererRef->get_window(), &windowWidth, &windowHeight);
	glm::vec2 pos{ offset,windowHeight - offset - m_pPacMan_Icon->GetSize().y };
	for(int i{0}; i < m_Lives; ++i)
	{
		m_pRendererRef->RenderTexture(*m_pPacMan_Icon, pos.x, pos.y);
		pos.x += offset + m_pPacMan_Icon->GetSize().x;
	}
}

void HUD::SetScoreTextComp(std::shared_ptr<textComponent> textComponent)
{
	m_pScoreText = std::move(textComponent);
}
