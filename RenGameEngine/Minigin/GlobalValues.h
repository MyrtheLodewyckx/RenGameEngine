#pragma once
#include "Singleton.h"
#include <vector>


class GlobalValues
{
public:
	static std::vector<int> m_Lives;
	static std::vector<int> m_Scores;
	static void Reset();
	GlobalValues();
	~GlobalValues() = default;
};