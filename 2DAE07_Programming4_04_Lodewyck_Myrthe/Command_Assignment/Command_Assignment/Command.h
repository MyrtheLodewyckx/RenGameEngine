#pragma once
#include <iostream>

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
	virtual void Execute() override { std::cout << "DANCE EXECUTED\n"; };
};

class Die :public Command
{
public:
	~Die() {};
	virtual void Execute() override { std::cout << "PLAYER EXECUTED\n";};
};


//BUTTONS ARE COUPLED IN INPUT.H