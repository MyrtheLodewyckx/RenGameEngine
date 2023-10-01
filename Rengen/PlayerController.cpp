#include "PlayerController.h"
#include "InputManager.h"



PlayerController::PlayerController()
{
	m_playerIdx = m_AmtOfPlayers;
	++m_AmtOfPlayers;
}