#pragma once
#include <iostream>
#include "Subject.h"
#include "EventManager.h"

class Command
{
public: 
	virtual ~Command() {}
	virtual void Execute() { std::cout<<"halp"; };
};


class Jump :public Command
{
public:
	~Jump() {};
	virtual void Execute() override { std::cout << "JUMP EXECUTED\n"; };
};

class Sing :public Command
{
public:
	~Sing() {};
	virtual void Execute() override { std::cout << "SING EXECUTED\n"; };
};

class Dance :public Command
{
public:
	~Dance() {};
	virtual void Execute() override 
	{ 
		dae::EventManager::GetInstance().AddEvent(Event::SCORE_CHANGE);
	};
};

class Die :public Command
{
public:
	~Die() {};
	virtual void Execute() override 
	{ 
		dae::EventManager::GetInstance().AddEvent(Event::PLAYER_DIES);
	};
};


//BUTTONS ARE COUPLED IN INPUT.H