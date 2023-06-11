#include "Physics.h"

#include <SDL_video.h>

#include "LevelManager.h"
#include "Renderer.h"

void Physics::Move(float deltaTime)
{
	auto pos = m_GameObject->GetGlobalPos();

	int row{}, column{};
	m_pLevelRef->PositionToIndex({ pos.x + m_Width * 0.5f,pos.y + m_Height * 0.5f }, column, row);
	const auto& cell = m_pLevelRef->m_Grid[row][column];
	const glm::vec3 cellCenter{ cell.boundingBox.x + cell.boundingBox.w * 0.5f, cell.boundingBox.y + cell.boundingBox.h * 0.5f,0 };

	glm::vec3 dir{};

	switch (m_CurrentDirection)
	{
	case CONNECTS_DOWN:
		dir.y = 1;
		pos.x = cellCenter.x - float(m_Width * 0.5);
		break;
	case CONNECTS_UP:
		dir.y = -1;
		pos.x = cellCenter.x - float(m_Width * 0.5);
		break;
	case CONNECTS_LEFT:
		dir.x = -1;
		pos.y = cellCenter.y - m_Height * 0.5f;
		break;
	case CONNECTS_RIGHT:
		dir.x = 1;
		pos.y = cellCenter.y - m_Height * 0.5f;
		break;
	case 0:
		m_GameObject->SetPosition(cellCenter.x - m_Width * 0.5f, cellCenter.y - m_Height * 0.5f, pos.z);
		return;
	}
	dir *= m_Speed * deltaTime;
	glm::vec3 newPos = pos + glm::vec3{ dir.x, dir.y, dir.z };

	if (newPos.x < -m_Width)
		newPos.x = (float)m_WindowWidth;
	else if (newPos.x > (float)m_WindowWidth)
		newPos.x = 1;

	m_GameObject->SetPosition(newPos);
}

Physics::Physics(dae::GameObject* go)
	:Component(go)
{
	SDL_GetWindowSize(dae::Renderer::GetInstance().get_window(), &m_WindowWidth, &m_WindowHeight);
}

void Physics::SetDimensions(int width, int height)
{
	m_Width = width;
	m_Height = height;
}
