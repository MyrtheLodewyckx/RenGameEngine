#pragma once
#include "Observer.h"
#include <vector>
#include <cassert>
static const int MAX_OBSERVERS = 10;

class Subject
{

protected:

	void Notify(Events event)
	{
		for (int i = 0; i < m_NumObservers; i++)
		{
			m_Observers[i]->OnNotify(event);
		}
	}

public:
	
	void addObserver(Observer* observer)
	{
		assert(m_NumObservers < MAX_OBSERVERS);

		m_Observers[m_NumObservers] = observer;
		++m_NumObservers;
	}


	//REWORK THIS!
	void removeObserver(Observer* observer)
	{
		for (int i{ 0 }; i < m_NumObservers; ++i)
		{
			if (m_Observers[i] == observer)
			{
				delete m_Observers[i];
				m_Observers[i] = nullptr;
			}
		}
	}

private:
	Observer* m_Observers[MAX_OBSERVERS];
	int m_NumObservers{0};
};