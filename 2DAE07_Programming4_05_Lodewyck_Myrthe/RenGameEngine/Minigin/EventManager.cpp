#include "MiniginPCH.h"
#include "EventManager.h"
#include <cassert>

void dae::EventManager::AddEvent(Event e)
{
	assert((m_Tail + 1) % MAX_EVENTS != m_Head);

	m_Events[m_Tail] = e;
	m_Tail = (m_Tail + 1) % MAX_EVENTS;
}

Event* dae::EventManager::GetEvent()
{
	if (m_Head == m_Tail) return nullptr;
	
	return &m_Events[m_Head];
}

void dae::EventManager::ProcessEvents()
{
	if (m_LastHeadEvent == m_Events[m_Head])
	{
		m_Events[m_Head] = Event(0);
		m_Head = (m_Head + 1) % MAX_EVENTS;
		if(m_Head == m_Tail+1)
			m_Head = (m_Head + 1) % MAX_EVENTS;
	}
	m_LastHeadEvent = m_Events[m_Head];
}




