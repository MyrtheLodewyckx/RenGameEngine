#pragma once
#include <iostream>
#include "Subject.h"
#include "EventManager.h"
#include "PlayerPhysics.h"
#include "GameStateManager.h"
#include "Scene.h"

using namespace dae;

class Command
{
public: 
	virtual ~Command() {}
	virtual void Execute(int) { std::cout<<"halp"; };
};


class ThrowPepper :public Command
{
public:
	~ThrowPepper() {};
	virtual void Execute(int playerIdx) override 
	{ 
		if(typeid(* GameStateManager::GetInstance().GetCurrent().get()) == typeid(Scene))
		PlayerPhysics::GetPlayer(playerIdx)->ThrowPepper();
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