#include "MiniginPCH.h"
#include "Player.h"
#include "EventManager.h"
#include "TextComponent.h"
#include "Transform.h"

void dae::Player::IncrementLives()
{
	++lives;
}

void dae::Player::DecrementLives()
{
	--lives;

	std::string newstr = "LIVES: " + std::to_string(lives);
	m_Go->GetComponent<TextComponent>()->SetText(newstr);

	if (lives == 0)
		dae::EventManager::GetInstance().AddEvent(Event::GAME_OVER);
}

void dae::Player::ChangeScore(int amt)
{
	score += amt;
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

	switch (*e)
	{
	case Event::PLAYER_DIES:
		DecrementLives();
		break;
	case Event::PLAYER_GAINS_LIFE:
		IncrementLives();
		break;
	}
}
