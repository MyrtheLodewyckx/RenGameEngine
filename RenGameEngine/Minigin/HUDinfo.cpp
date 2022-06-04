#include "MiniginPCH.h"
#include "HUDinfo.h"
#include "EventManager.h"
#include "TextComponent.h"
#include "Transform.h"
#include "Audio.h"
#include "InputManager.h"

void dae::HUD::IncrementLives()
{
	*m_Lives += 1;
}

void dae::HUD::DecrementLives()
{
	*m_Lives -= 1;

	std::string newstr = "LIVES: " + std::to_string(*m_Lives);
	m_Go->GetComponent<TextComponent>()->SetText(newstr);

	sound_system* a = &AudioServiceLocator::get_sound_system();
	a->Play((int)SoundId::PLAYER_DIES, 50);

	if (m_Lives == 0)
	{
		Event* e = new Event{};
		e->ID = Events::GAME_OVER;
		dae::EventManager::GetInstance().AddEvent(e);
	}
	else
	{
		Event* e = new Event{};
		e->ID = Events::RESTART_LEVEL;
		dae::EventManager::GetInstance().AddEvent(e);
	}
}

void dae::HUD::ChangeScore(int amt)
{
	m_Score += amt;
	std::string newstr = "SCORE: " + std::to_string(m_Score);
	auto g = m_Go->GetChildAt(0)->GetComponent<TextComponent>();
	g->SetText(newstr);

	sound_system* a = &AudioServiceLocator::get_sound_system();
	a->Play((int)SoundId::SCORE_UP, 50);
}

void dae::HUD::SetGlobalVariables(int& lives)
{
	m_Lives = &lives;
}

void dae::HUD::Update(const float)
{
	HandleEvents();
}

void dae::HUD::HandleEvents()
{
	auto e = dae::EventManager::GetEvent();

	if (e == nullptr)
		return;

	switch (e->ID)
	{
	case Events::PLAYER_DIES:
	{
		auto p = dynamic_cast<PlayerDiesEvent*>(e);
		if (p->controllerIdx == m_PlayerIdx)
			DecrementLives();
		break;
	}
	case Events::PLAYER_GAINS_LIFE:
		IncrementLives();
		break;
	case Events::SCORE_CHANGE:
	{
		auto p = dynamic_cast<ScoreChangeEvent*>(e);
		if (p->controllerIdx == m_PlayerIdx)
		ChangeScore(p->amt);
		break;
	}
	}
}
