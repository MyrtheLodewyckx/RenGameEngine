#pragma once
#include <iostream>
#include "Subject.h"
#include "EventManager.h"

class Command
{
public: 
	virtual ~Command() {}
	virtual void Execute(int) { std::cout<<"halp"; };
};


class Jump :public Command
{
public:
	~Jump() {};
	virtual void Execute(int) override { std::cout << "JUMP EXECUTED\n"; };
};

class Select :public Command
{
public:
	~Select() {};
	virtual void Execute(int) override 
	{ 
		Event* e = new Event{};
		e->ID = (int)Events::BUTTON_SELECT;
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
		e->ID = (int)Events::GAME_PAUSE;
		dae::EventManager::GetInstance().AddEvent(e);
	}
};

class Left :public Command
{
public:
	~Left() {};
	virtual void Execute(int) override
	{
		Event* e = new Event{};
		e->ID = (int)Events::BUTTON_LEFT;
		dae::EventManager::GetInstance().AddEvent(e);
	}
};

class Right :public Command
{
public:
	~Right() {};
	virtual void Execute(int) override
	{
		Event* e = new Event{};
		e->ID = (int)Events::BUTTON_RIGHT;
		dae::EventManager::GetInstance().AddEvent(e);
	}
};

class Up :public Command
{
public:
	~Up() {};
	virtual void Execute(int) override
	{
		Event* e = new Event{};
		e->ID = (int)Events::BUTTON_UP;
		dae::EventManager::GetInstance().AddEvent(e);
	}
};

class Down :public Command
{
public:
	~Down() {};
	virtual void Execute(int) override
	{
		Event* e = new Event{};
		e->ID = (int)Events::BUTTON_DOWN;
		dae::EventManager::GetInstance().AddEvent(e);
	}
};