#pragma once
#include "Singleton.h"
#include "Events.h"

#include <array>
#include <cassert>
#include <memory>

namespace dae
{

	class EventManager : public Singleton<EventManager>
	{
		static constexpr int MAX_EVENTS = 16;

		int m_Head{ 0 };
		int m_Tail{ 0 };

		std::array<std::unique_ptr<Event>, MAX_EVENTS> m_Events{};

	public:

		// Preferred: pass ownership in
		void AddEvent(std::unique_ptr<Event> e);
		Event* GetEvent() const;
		void ProcessEvents();
		bool HasEvent() const { return m_Head != m_Tail; }
	};
}