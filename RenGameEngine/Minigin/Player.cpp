#include "MiniginPCH.h"
#include "Player.h"
#include "EventManager.h"
#include "TextComponent.h"
#include "Transform.h"
#include "Audio.h"
#include "InputManager.h"

void dae::Player::IncrementLives()
{
	++lives;
}

void dae::Player::DecrementLives()
{
	--lives;

	std::string newstr = "LIVES: " + std::to_string(lives);
	m_Go->GetComponent<TextComponent>()->SetText(newstr);

	sound_system* a = &AudioServiceLocator::get_sound_system();
	a->Play((int)SoundId::PLAYER_DIES, 50);

	if (lives == 0)
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

void dae::Player::ChangeScore(int amt)
{
	score += amt;
	std::string newstr = "SCORE: " + std::to_string(score);
	auto g = m_Go->GetChildAt(0)->GetComponent<TextComponent>();
	g->SetText(newstr);

	sound_system* a = &AudioServiceLocator::get_sound_system();
	a->Play((int)SoundId::SCORE_UP, 50);
}

void dae::Player::Update(const float)
{
	HandleEvents();
}

void dae::Player::HandleEvents()
{
	auto e = dae::EventManager::GetEvent();

	if (e == nullptr)
		return;

	switch (e->ID)
	{
	case Events::PLAYER_DIES:
	{
		auto p = dynamic_cast<PlayerDiesEvent*>(e);
		if (p->controllerIdx == m_ControllerIdx)
			DecrementLives();
		break;
	}
	case Events::PLAYER_GAINS_LIFE:
		IncrementLives();
		break;
	case Events::SCORE_CHANGE:
	{
		auto p = dynamic_cast<ScoreChangeEvent*>(e);
		if (p->controllerIdx == m_ControllerIdx)
		ChangeScore(p->amt);
		break;
	}
	}
}
