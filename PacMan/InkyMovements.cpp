#include "InkyMovements.h"

#include <glm/geometric.hpp>

void InkyMovement::Update(const float deltaTime)
{
	int row{}, column{};
	glm::vec2 centerPos{ m_GameObject->GetGlobalPos().x + m_Width * 0.5f,m_GameObject->GetGlobalPos().y + m_Height * 0.5f };

	m_pLevelRef->PositionToIndex(centerPos, column, row);


	if (row != m_CurrentRow || column != m_CurrentColumn)
	{
		m_CurrentRow = row;
		m_CurrentColumn = column;

		//GET CLOSEST PACMAN
		float distance{ FLT_MAX };
		int idx{};
		for (int i{ 0 }; i < (int)m_Players.size(); ++i)
		{
			glm::vec3 vec = m_Players[i]->GetGlobalPos() - glm::vec3{ centerPos.x,centerPos.y,0 };
			auto length = glm::length(vec);
			if (length < distance)
			{
				distance = length;
				idx = i;
			}
		}


		glm::vec3 targetPos{ m_Players[idx]->GetGlobalPos() };
		float targetDistance{ 50.f };

		if (distance < targetDistance)
		targetDistance = distance;

		glm::vec3 dir{};
		switch(m_PacManPhysics[idx]->GetDirection())
		{
		case (int)CONNECTS_LEFT:
			dir.x = -targetDistance;
			break;
		case (int)CONNECTS_RIGHT:
			dir.x = targetDistance;
			break;
		case (int)CONNECTS_UP:
			dir.y = -targetDistance;
			break;
		case (int)CONNECTS_DOWN:
			dir.y = targetDistance;
			break;
		}
		targetPos += dir;

		if (m_IsFleeing)
			SetFleeDirection({ centerPos.x, centerPos.y,0 }, targetPos);
		else
			SetDirection({ centerPos.x, centerPos.y,0 }, targetPos);

	}
	Move(deltaTime);
}

void InkyMovement::FixedUpdate(const float)
{
}

void InkyMovement::Initialize()
{
	GhostMovement::Initialize();
	for(const auto& pacman: m_Players)
	{
		m_PacManPhysics.emplace_back(pacman->GetComponent<Physics>().get());
	}
}
