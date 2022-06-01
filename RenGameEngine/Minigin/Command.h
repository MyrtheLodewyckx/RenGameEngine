#pragma once
#include <iostream>
#include "Subject.h"
#include "EventManager.h"
#include "PlayerPhysics.h"

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
	virtual void Execute(int controllerIdx) override 
	{ 
		dae::PlayerPhysics::GetPlayer(controllerIdx)->ThrowPepper();
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
		dae::EventManager::GetInstance().AddEvent(e);
	};
};

class Dance :public Command
{
public:
	~Dance() {};
	virtual void Execute(int controllerIdx) override
	{ 
		ScoreChangeEvent* e = new ScoreChangeEvent{};
		e->amt = 10;
		e->controllerIdx = controllerIdx;
		dae::EventManager::GetInstance().AddEvent(e);
	};
};

class Die :public Command
{
public:
	~Die() {};
	virtual void Execute(int controllerIdx) override
	{ 
		PlayerDiesEvent* e = new PlayerDiesEvent{};
		e->controllerIdx = controllerIdx;
		dae::EventManager::GetInstance().AddEvent(e);
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
		dae::EventManager::GetInstance().AddEvent(e);
	}
};