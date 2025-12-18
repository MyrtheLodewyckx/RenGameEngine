#include "EventManager.h"
#include <cassert>

void dae::EventManager::AddEvent(Event* e)
{
	assert((m_Tail + 1) % MAX_EVENTS != m_Head);

	m_Events[m_Tail] = e;
	m_Tail = (m_Tail + 1) % MAX_EVENTS;
}

Event* dae::EventManager::GetEvent() const
{
	if(m_Head == m_Tail) return nullptr;

	return m_Events[m_Head];
}


void dae::EventManager::ProcessEvents()
{
	if (m_Head == m_Tail) return;

	delete m_Events[m_Head];
	m_Events[m_Head] = nullptr;
	m_Head = (m_Head + 1) % MAX_EVENTS;
}
