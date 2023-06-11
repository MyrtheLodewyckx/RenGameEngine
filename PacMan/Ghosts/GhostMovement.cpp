#include "GhostMovement.h"

#include <glm/geometric.hpp>

#include "Renderer.h"
#include "../PacMan.h"

void GhostMovement::SetDirection(glm::vec3 startPos, glm::vec3 target)
{
	//GetNewDirection
	int dirFlags{};
	m_pLevelRef->GetDirectionFlags(startPos, dirFlags);
	float distance{ FLT_MAX };
	int currentFlag{ 1 };
	for (int i{ 0 }; i < 4; ++i)
	{
		if ((dirFlags & currentFlag) == currentFlag)
		{
			auto vec = glm::vec3{ m_pLevelRef->GetTo(startPos, currentFlag)->boundingBox.x, m_pLevelRef->GetTo({startPos.x, startPos.y}, currentFlag)->boundingBox.y,0 } - target;
			auto length = glm::length(vec);
			if (length < distance)
			{
				distance = length;
				m_CurrentDirection = currentFlag;
			}
		}

		currentFlag = currentFlag << 1;
	}
}

void GhostMovement::SetFleeDirection(glm::vec3 startPos, glm::vec3 target)
{
	//GetNewDirection
	int dirFlags{};
	m_pLevelRef->GetDirectionFlags(startPos, dirFlags);
	float distance{ 0 };
	int currentFlag{ 1 };
	for (int i{ 0 }; i < 4; ++i)
	{
		if ((dirFlags & currentFlag) == currentFlag)
		{

			auto vec = glm::vec3{ m_pLevelRef->GetTo(startPos, currentFlag)->boundingBox.x, m_pLevelRef->GetTo({startPos.x, startPos.y}, currentFlag)->boundingBox.y,0 } - target;
			auto length = glm::length(vec);
			if (length > distance)
			{
				distance = length;
				m_CurrentDirection = currentFlag;
			}
		}

		currentFlag = currentFlag << 1;
	}
}

void GhostMovement::Initialize()
{
	m_Players = dae::SceneManager::GetInstance().GetCurrentScene()->GetAllGameObjectsWithComponent<PacMan>();
	SDL_GetWindowSize(dae::Renderer::GetInstance().get_window(), &m_WindowWidth, &m_WindowHeight);
	m_Speed = 80;
}

void GhostMovement::SetFlee(bool isFleeing)
{
	m_IsFleeing = isFleeing;
}



