#include "MiniginPCH.h"
#include "Player.h"
#include "EventManager.h"
#include "TextComponent.h"
#include "Transform.h"
#include "Achivements.h"
#include "Audio.h"

void dae::Player::IncrementLives()
{
	++lives;
}

void dae::Player::DecrementLives()
{
	--lives;

	std::string newstr = "LIVES: " + std::to_string(lives);
	m_Go->GetComponent<TextComponent>()->SetText(newstr);

	sound_system* a = &ServiceLocator::get_sound_system();
	a->Play((int)SoundId::PLAYER_DIES, 50);

	if (lives == 0)
	{
		Event* e = new Event{};
		e->ID = (int)Events::GAME_OVER;
		dae::EventManager::GetInstance().AddEvent(e);
	}
}

void dae::Player::ChangeScore(int amt)
{
	score += amt;
	std::string newstr = "SCORE: " + std::to_string(score);
	auto g = m_Go->GetChildAt(0)->GetComponent<TextComponent>();
	g->SetText(newstr);

	sound_system* a = &ServiceLocator::get_sound_system();
	a->Play((int)SoundId::SCORE_UP, 50);

	if (score > 500 && SteamAchievements::GetInstance().g_SteamAchievements)
	SteamAchievements::GetInstance().g_SteamAchievements->SetAchievement("ACH_TRAVEL_FAR_ACCUM");
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
	case (int)Events::PLAYER_DIES:
	{
		auto p = dynamic_cast<PlayerDiesEvent*>(e);
		if (p->controllerIdx == m_ControllerIdx)
			DecrementLives();
		break;
	}
	case (int)Events::PLAYER_GAINS_LIFE:
		IncrementLives();
		break;
	case (int)Events::SCORE_CHANGE:
	{
		auto p = dynamic_cast<ScoreChangeEvent*>(e);
		if (p->controllerIdx == m_ControllerIdx)
		ChangeScore(p->amt);
		break;
	}
	}
}
