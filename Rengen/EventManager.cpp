#include "EventManager.h"
#include <cassert>



void dae::EventManager::AddEvent(std::unique_ptr<Event> e)
{
	assert(e);

	const int nextTail = (m_Tail + 1) % MAX_EVENTS;

	assert(nextTail != m_Head);

	m_Events[m_Tail] = std::move(e);
	m_Tail = nextTail;
}

Event* dae::EventManager::GetEvent() const
{
	if(m_Head == m_Tail) return nullptr;

	return m_Events[m_Head].get();
}


void dae::EventManager::ProcessEvents()
{
	if (m_Head == m_Tail) return;

	m_Events[m_Head].reset();
	m_Head = (m_Head + 1) % MAX_EVENTS;
}
