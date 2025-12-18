#pragma once
#include "Singleton.h"
#include "Events.h"

namespace dae
{

	class EventManager : public Singleton<EventManager>
	{
		static constexpr int MAX_EVENTS = 16;

		int m_Head{ 0 };
		int m_Tail{ 0 };

		Event* m_Events[MAX_EVENTS]{ nullptr };

	public:
		void AddEvent(Event* e);
		Event* GetEvent() const;
		void ProcessEvents();
		bool HasEvent() const { return m_Head != m_Tail; }
	};
}