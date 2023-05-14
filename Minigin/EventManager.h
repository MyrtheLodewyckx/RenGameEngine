#pragma once
#include "Singleton.h"
#include "Events.h"

namespace dae
{
	static const int MAX_EVENTS = 16;
	static int m_Head{ 0 };
	static int m_Tail{ 0 };
	static Event* m_LastHeadEvent;
	static Event* m_Events[MAX_EVENTS];

	class EventManager : public Singleton<EventManager>
	{
	public:
		void AddEvent(Event* e);
		static Event* GetEvent();
		void ProcessEvents();
	};
}