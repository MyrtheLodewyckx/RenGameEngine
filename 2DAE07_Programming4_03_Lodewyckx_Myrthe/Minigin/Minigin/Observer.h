#pragma once
enum struct Event
{
	PLAYER_DIES,
	PLAYER_GAINS_LIFE
};

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void OnNotify(Event) = 0;
};