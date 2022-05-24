#pragma once
enum struct Events
{
	//PLAYER EVENTS
	PLAYER_DIES = 1,
	PLAYER_GAINS_LIFE = 2,
	SCORE_CHANGE = 3,

	//GAME EVENTS
	GAME_OVER = 4,
	GAME_PAUSE = 5,

	//DIRECTIONAL BUTTON
	BUTTON_LEFT = 6,
	BUTTON_RIGHT = 7,
	BUTTON_DOWN = 8,
	BUTTON_UP = 9,

	BUTTON_SELECT = 10
};

struct Event
{
	int ID = 0;
	virtual void PrintExtraInfo() { std::cout << "No extra info\n"; }
};

struct PlayerDiesEvent: public Event
{
	PlayerDiesEvent() { ID = (int)Events::PLAYER_DIES; }
	int controllerIdx = 0;
	virtual void PrintExtraInfo() override { std::cout << "controllerIdx: " << controllerIdx <<'\n'; }
};

struct PlayerGainsLifeEvent : public Event
{
	PlayerGainsLifeEvent() { ID = (int)Events::PLAYER_GAINS_LIFE; }
	int controllerIdx = 0;
	virtual void PrintExtraInfo() override { std::cout << "controllerIdx: " << controllerIdx << '\n'; }
};

struct ScoreChangeEvent : public Event
{
	ScoreChangeEvent() {
		ID = (int)Events::SCORE_CHANGE;}
	int controllerIdx = 0;
	int amt = 0;
	virtual void PrintExtraInfo() override { std::cout << "controllerIdx: " << controllerIdx << '\n'; }
};


//Use eventArgs
enum struct buttonEvents
{


};