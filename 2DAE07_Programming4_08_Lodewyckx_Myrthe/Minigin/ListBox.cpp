#include "MiniginPCH.h"
#include "ListBox.h"
#include "EventManager.h"
#include "InputManager.h"

void dae::ListBox::update()
{
	auto e = dae::EventManager::GetEvent();

	if (e == nullptr)
		return;

	switch (e->ID)
	{
	case (int)Events::BUTTON_UP:
		m_ButtonIdx = (m_ButtonIdx - 1)% maxButtonsToChange;
		break;
	case (int)Events::BUTTON_DOWN:
		m_ButtonIdx = (m_ButtonIdx + 1) % maxButtonsToChange;
	}
}

void dae::ListBox::render()
{
}
