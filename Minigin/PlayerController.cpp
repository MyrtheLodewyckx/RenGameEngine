#include "PlayerController.h"
#include "InputManager.h"



PlayerController::PlayerController(dae::GameObject* go)
:Component(go)
{
	m_playerIdx = m_AmtOfPlayers;
	++m_AmtOfPlayers;
}