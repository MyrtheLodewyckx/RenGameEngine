#include "MiniginPCH.h"
#include "GlobalValues.h"
#include "EventManager.h"

std::vector<int> GlobalValues::m_Lives{3};
std::vector<int> GlobalValues::m_Scores{0};

GlobalValues::GlobalValues()
{}

void GlobalValues::Reset()
{
	for (int i = 0; i < (int)m_Lives.size(); ++i)
	{
		m_Lives[i] = 3;
	}
	for (int i = 0; i < (int)m_Scores.size(); ++i)
	{
		m_Scores[i] = 0;
	}
}
