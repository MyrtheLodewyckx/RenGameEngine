#include "MiniginPCH.h"
#include "Player.h"

void Player::IncrementLives()
{
	++lives;
}

void Player::DecrementLives()
{
	--lives;
}

void Player::ChangeScore(int amt)
{
	score += amt;
}

void Player::OnNotify(Event event)
{
	switch (event)
	{
	case Event::PLAYER_DIES:
		DecrementLives();
		break;
	case Event::PLAYER_GAINS_LIFE:
		IncrementLives();
		break;
	}
}
