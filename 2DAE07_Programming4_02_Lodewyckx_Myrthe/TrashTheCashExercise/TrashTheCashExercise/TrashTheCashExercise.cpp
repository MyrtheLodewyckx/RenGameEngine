// TrashTheCashExercise.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <vector>
#include "GameObject3D.h"

int main()
{
	std::cout << "EXCERSIZE 1: INTEGERS\n";
	std::vector<int> integers{};
	integers.resize(100000000);
	int stepsize{ 1 };

	auto timeLast = std::chrono::high_resolution_clock::now();
	auto timeNow = std::chrono::high_resolution_clock::now();

	while (stepsize <= 1024)
	{
		for (int i{ 0 }; i < integers.size(); i += stepsize)
		{
			integers[i] *= 2;
		}
		timeNow = std::chrono::high_resolution_clock::now();

		std::cout << "Stepsize " << stepsize << "	:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - timeLast).count() << '\n';

		stepsize *= 2;
		timeLast = std::chrono::high_resolution_clock::now();
	}

	/// Now with class objects
	std::cout << "_________________________________________________________\n";
	std::cout << "EXCERSIZE 2: GAMEOBJECT3DIN\n";

	std::vector<GameObject3D> objs{};
	objs.resize(100000000);

	stepsize = 1;
	timeLast = std::chrono::high_resolution_clock::now();

	while (stepsize <= 1024)
	{
		for (int i{ 0 }; i < objs.size(); i += stepsize)
		{
			objs[i].SetId(2);
		}
		timeNow = std::chrono::high_resolution_clock::now();

		std::cout << "Stepsize " << stepsize << "	:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - timeLast).count() << '\n';

		stepsize *= 2;
		timeLast = std::chrono::high_resolution_clock::now();
	}


}