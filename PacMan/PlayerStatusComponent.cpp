#include "PlayerStatusComponent.h"

void PlayerStatusComponent::onNotify(playerEvents event, int amt)
{
	switch(event)
	{
	case playerEvents::SCORE_CHANGE:
		ChangeScore(amt);
		break;
	case playerEvents::LIVES_CHANGE:
		ChangeLives(amt);
		break;
	}
}
