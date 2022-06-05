#pragma once
#include "Events.h"

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void OnNotify(Events) = 0;
};