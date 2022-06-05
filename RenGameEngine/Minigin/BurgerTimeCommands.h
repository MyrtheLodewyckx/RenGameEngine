#pragma once
#include "Command.h"
#include "GameStateManager.h"
#include "Scene.h"
#include "Player.h"
#include "Events.h"
#include "EVentManager.h"

using namespace dae;

class ThrowPepper :public Command
{
public:
	~ThrowPepper() {};
	virtual void Execute(int playerIdx) override
	{
		if (typeid(*GameStateManager::GetInstance().GetCurrent().get()) == typeid(Scene))
			Player::GetPlayer(playerIdx)->ThrowPepper();
	};
};
class Select :public Command
{
public:
	~Select() {};
	virtual void Execute(int) override
	{
		Event* e = new Event{};
		e->ID = Events::BUTTON_SELECT;
		EventManager::GetInstance().AddEvent(e);
	};
};

class Menu :public Command
{
public:
	~Menu() {};
	virtual void Execute(int) override
	{
		Event* e = new Event{};
		e->ID = Events::GAME_PAUSE;
		EventManager::GetInstance().AddEvent(e);
	}
};