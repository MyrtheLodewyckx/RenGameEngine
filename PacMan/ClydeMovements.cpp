#include "ClydeMovements.h"

#include <algorithm>
#include <glm/detail/func_geometric.inl>

#include "ResourceManager.h"
#include "Scene.h"


void ClydeMovement::Update(const float deltaTime)
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

		if (m_IsFleeing)
			SetFleeDirection({ centerPos.x, centerPos.y,0 }, m_Players[idx]->GetGlobalPos());
		else
			SetDirection({ centerPos.x, centerPos.y,0 }, m_Players[idx]->GetGlobalPos());

	}
	Move(deltaTime);

	m_Timer += deltaTime;
	if (m_IsFleeing)
	{
		const float fleeTime{ 4.f };
		if (m_Timer >= fleeTime)
		{
			m_Timer = 0.f;
			m_IsFleeing = false;
		}
	}
	else
	{
		const float chaseTime{ 10.f };
		if (m_Timer >= chaseTime)
		{
			m_Timer = 0.f;
			m_IsFleeing = true;
		}
	}
}

void ClydeMovement::FixedUpdate(const float)
{

}

