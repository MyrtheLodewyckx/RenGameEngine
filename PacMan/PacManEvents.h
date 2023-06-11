#pragma once
#include "Events.h"

enum class PacManEvents
{
	SCORE_CHANGE,
	LIVES_CHANGE,
	WIN,
	LOSE,
	POWER_PELLET_EAT
};

struct SCORE_CHANGE : Event
{
	SCORE_CHANGE() { ID = static_cast<int>(PacManEvents::SCORE_CHANGE); }
	~SCORE_CHANGE() override = default;
	int amt{};
};

struct WIN : Event
{
	WIN() { ID = static_cast<int>(PacManEvents::WIN); }
	~WIN() override = default;
	int amt{};
};

struct LOSE : Event
{
	LOSE() { ID = static_cast<int>(PacManEvents::LOSE); }
	~LOSE() override = default;
	int amt{};
};

struct LIVES_CHANGE : Event
{
	LIVES_CHANGE() { ID = static_cast<int>(PacManEvents::LIVES_CHANGE); }
	~LIVES_CHANGE() override = default;
	int amt{};
};

struct POWER_PELLET_EAT : Event
{
	POWER_PELLET_EAT() { ID = static_cast<int>(PacManEvents::POWER_PELLET_EAT); }
	~POWER_PELLET_EAT() override = default;
};