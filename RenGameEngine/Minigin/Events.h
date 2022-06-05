#pragma once
#include <iostream>
enum struct Events
{
	//PLAYER EVENTS
	PLAYER_DIES = 1,
	PLAYER_GAINS_LIFE = 2,
	SCORE_CHANGE = 3,
	PEPPER_CHANGE,

	//LEVEL EVENTS
	RESTART_LEVEL,
	NEXT_LEVEL,

	//GAME EVENTS
	GAME_OVER = 4,
	GAME_PAUSE = 5,

	//DIRECTIONAL BUTTON
	BUTTON_SELECT = 10
};

struct Event
{
	Events ID = (Events)0;
	virtual void PrintExtraInfo() { std::cout << "No extra info\n"; }
};

struct PlayerDiesEvent: public Event
{
	PlayerDiesEvent() { ID = Events::PLAYER_DIES; }
	int controllerIdx = 0;
	virtual void PrintExtraInfo() override { std::cout << "controllerIdx: " << controllerIdx <<'\n'; }
};

struct PlayerGainsLifeEvent : public Event
{
	PlayerGainsLifeEvent() { ID = Events::PLAYER_GAINS_LIFE; }
	int controllerIdx = 0;
	virtual void PrintExtraInfo() override { std::cout << "controllerIdx: " << controllerIdx << '\n'; }
};

struct ScoreChangeEvent : public Event
{
	ScoreChangeEvent() {
		ID = Events::SCORE_CHANGE;}
	int controllerIdx = 0;
	int amt = 0;
	virtual void PrintExtraInfo() override { std::cout << "controllerIdx: " << controllerIdx << '\n'; }
};

struct PepperChangeEvent : public Event
{
	PepperChangeEvent() {
		ID = Events::PEPPER_CHANGE;
	}
	int PlayerIdx = 0;
	int amt = 0;
	virtual void PrintExtraInfo() override { std::cout << "PlayerIdx: " << PlayerIdx << '\n'; }
};


//Use eventArgs