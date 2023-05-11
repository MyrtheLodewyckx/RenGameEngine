#include "GameStateManager.h"
#include "ResourceManager.h"

void dae::GameStateManager::Add(std::unique_ptr<GameState> toAdd, bool replace)
{
	m_add = true;
	m_newState = std::move(toAdd);
	m_replace = replace;
}

void dae::GameStateManager::PopCurrent()
{
	m_remove = true;
}

void dae::GameStateManager::ProcessStateChange()
{
	if (m_remove && !m_StateStack.empty())
	{
		m_StateStack.pop();

		if (!m_StateStack.empty())
			m_StateStack.top()->Start();

		m_remove = false;
	}

	if (m_add)
	{
		if (m_replace && !m_StateStack.empty())
		{
			m_StateStack.pop();
			m_replace = false;
		}

		if (!m_StateStack.empty())
		{
			m_StateStack.top()->Pause();
		}

		m_newState->Initialize();
		m_StateStack.push(std::move(m_newState));
		m_add = false;
	}
}

std::unique_ptr<dae::GameState>& dae::GameStateManager::GetCurrent()
{
	return m_StateStack.top();
}
