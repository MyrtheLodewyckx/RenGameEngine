#pragma once
#include <iostream>


class Event
{
public:
	Event() = default;
	virtual ~Event() = default;
	int ID {};
	virtual void PrintExtraInfo() { std::cout << "No extra info\n"; }
};

//Use eventArgs