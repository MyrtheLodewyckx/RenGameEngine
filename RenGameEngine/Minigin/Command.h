#pragma once
#include <iostream>


class Command
{
public: 
	virtual ~Command() {}
	virtual void Execute(int) { std::cout<<"halp"; };
};


