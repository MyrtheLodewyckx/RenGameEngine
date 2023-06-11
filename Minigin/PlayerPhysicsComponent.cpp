#include "PlayerPhysicsComponent.h"

#include <iostream>

#include "GameObject.h"
#include "InputManager.h"
#include "Controller.h"
#include "Keyboard.h"
#include "Renderer.h"

void MoveCommand::Execute(float x, float y, const float)
{
	if (m_IsDying)
	{
		*m_CurrentDirection = 0;
		return;
	}

	if(!(abs(x) < 0.001f && abs(y) < 0.001f))
	if (abs(x) > abs(y))
	{
		if (x < 0)
			m_DirectionInput = CONNECTS_LEFT;
		else m_DirectionInput = CONNECTS_RIGHT;
	}
	else
	{
		if (y < 0)
			m_DirectionInput = CONNECTS_DOWN;
		else m_DirectionInput = CONNECTS_UP;
	}


	int row{};
	int column{};

	glm::vec2 pos{ player->GetGlobalPos().x + m_Width * 0.5f, player->GetGlobalPos().y + m_Height * 0.5f };

	m_pLevelRef->PositionToIndex(pos, column, row);
	auto cell = m_pLevelRef->m_Grid[row][column];
	glm::vec2 cellCenter{ cell.boundingBox.x + cell.boundingBox.w / 2,cell.boundingBox.y + cell.boundingBox.h / 2 };


	if (*m_CurrentDirection == 0)
	{
		m_pLevelRef->GetDirectionFlags(row, column, m_AvailableDirection);
		if ((m_AvailableDirection & m_DirectionInput) == m_DirectionInput)
		{
			*m_CurrentDirection = m_DirectionInput;
		}
	}

	if (*m_CurrentDirection == CONNECTS_LEFT && pos.x < cellCenter.x ||
		*m_CurrentDirection == CONNECTS_RIGHT && pos.x > cellCenter.x ||
		*m_CurrentDirection == CONNECTS_UP && pos.y < cellCenter.y ||
		*m_CurrentDirection == CONNECTS_DOWN && pos.y > cellCenter.y)
	{
		//player->SetPosition(cellCenter.x - m_Width*0.5f, cellCenter.y- m_Height*0.5f, 0);
		m_pLevelRef->GetDirectionFlags(row, column, m_AvailableDirection);
		if ((m_AvailableDirection & m_DirectionInput) != m_DirectionInput)
		{
			*m_CurrentDirection = 0;
		}
		else *m_CurrentDirection = m_DirectionInput;
	}

}

void MoveLeftCommand::Execute()
{
	if (m_IsDying)
	{
		*m_CurrentDirection = 0;
		return;
	}

	m_DirectionInput = CONNECTS_LEFT;

	int row{};
	int column{};

	glm::vec2 pos{ player->GetGlobalPos().x + m_Width * 0.5f, player->GetGlobalPos().y + m_Height * 0.5f };

	m_pLevelRef->PositionToIndex(pos, column, row);
	auto cell = m_pLevelRef->m_Grid[row][column];
	glm::vec2 cellCenter{ cell.boundingBox.x + cell.boundingBox.w / 2,cell.boundingBox.y + cell.boundingBox.h / 2 };


	if (*m_CurrentDirection == 0)
	{
		m_pLevelRef->GetDirectionFlags(row, column, m_AvailableDirection);
		if ((m_AvailableDirection & m_DirectionInput) == m_DirectionInput)
		{
			*m_CurrentDirection = m_DirectionInput;
		}
	}

	if (*m_CurrentDirection == CONNECTS_LEFT && pos.x < cellCenter.x ||
		*m_CurrentDirection == CONNECTS_RIGHT && pos.x > cellCenter.x ||
		*m_CurrentDirection == CONNECTS_UP && pos.y < cellCenter.y ||
		*m_CurrentDirection == CONNECTS_DOWN && pos.y > cellCenter.y)
	{
		//player->SetPosition(cellCenter.x - m_Width*0.5f, cellCenter.y- m_Height*0.5f, 0);
		m_pLevelRef->GetDirectionFlags(row, column, m_AvailableDirection);
		if ((m_AvailableDirection & m_DirectionInput) != m_DirectionInput)
		{
			*m_CurrentDirection = 0;
		}
		else *m_CurrentDirection = m_DirectionInput;
	}

}

void MoveRightCommand::Execute()
{
	if (m_IsDying)
	{
		*m_CurrentDirection = 0;
		return;
	}

	m_DirectionInput = CONNECTS_RIGHT;

	int row{};
	int column{};

	glm::vec2 pos{ player->GetGlobalPos().x + m_Width * 0.5f, player->GetGlobalPos().y + m_Height * 0.5f };

	m_pLevelRef->PositionToIndex(pos, column, row);
	auto cell = m_pLevelRef->m_Grid[row][column];
	glm::vec2 cellCenter{ cell.boundingBox.x + cell.boundingBox.w / 2,cell.boundingBox.y + cell.boundingBox.h / 2 };


	if (*m_CurrentDirection == 0)
	{
		m_pLevelRef->GetDirectionFlags(row, column, m_AvailableDirection);
		if ((m_AvailableDirection & m_DirectionInput) == m_DirectionInput)
		{
			*m_CurrentDirection = m_DirectionInput;
		}
	}

	if (*m_CurrentDirection == CONNECTS_LEFT && pos.x < cellCenter.x ||
		*m_CurrentDirection == CONNECTS_RIGHT && pos.x > cellCenter.x ||
		*m_CurrentDirection == CONNECTS_UP && pos.y < cellCenter.y ||
		*m_CurrentDirection == CONNECTS_DOWN && pos.y > cellCenter.y)
	{
		//player->SetPosition(cellCenter.x - m_Width*0.5f, cellCenter.y- m_Height*0.5f, 0);
		m_pLevelRef->GetDirectionFlags(row, column, m_AvailableDirection);
		if ((m_AvailableDirection & m_DirectionInput) != m_DirectionInput)
		{
			*m_CurrentDirection = 0;
		}
		else *m_CurrentDirection = m_DirectionInput;
	}
}

void MoveDownCommand::Execute()
{
	if (m_IsDying)
	{
		*m_CurrentDirection = 0;
		return;
	}

	m_DirectionInput = CONNECTS_DOWN;

	int row{};
	int column{};

	glm::vec2 pos{ player->GetGlobalPos().x + m_Width * 0.5f, player->GetGlobalPos().y + m_Height * 0.5f };

	m_pLevelRef->PositionToIndex(pos, column, row);
	auto cell = m_pLevelRef->m_Grid[row][column];
	glm::vec2 cellCenter{ cell.boundingBox.x + cell.boundingBox.w / 2,cell.boundingBox.y + cell.boundingBox.h / 2 };


	if (*m_CurrentDirection == 0)
	{
		m_pLevelRef->GetDirectionFlags(row, column, m_AvailableDirection);
		if ((m_AvailableDirection & m_DirectionInput) == m_DirectionInput)
		{
			*m_CurrentDirection = m_DirectionInput;
		}
	}

	if (*m_CurrentDirection == CONNECTS_LEFT && pos.x < cellCenter.x ||
		*m_CurrentDirection == CONNECTS_RIGHT && pos.x > cellCenter.x ||
		*m_CurrentDirection == CONNECTS_UP && pos.y < cellCenter.y ||
		*m_CurrentDirection == CONNECTS_DOWN && pos.y > cellCenter.y)
	{
		//player->SetPosition(cellCenter.x - m_Width*0.5f, cellCenter.y- m_Height*0.5f, 0);
		m_pLevelRef->GetDirectionFlags(row, column, m_AvailableDirection);
		if ((m_AvailableDirection & m_DirectionInput) != m_DirectionInput)
		{
			*m_CurrentDirection = 0;
		}
		else *m_CurrentDirection = m_DirectionInput;
	}
}

void MoveUpCommand::Execute()
{
	if (m_IsDying)
	{
		*m_CurrentDirection = 0;
		return;
	}

	m_DirectionInput = CONNECTS_UP;

	int row{};
	int column{};

	glm::vec2 pos{ player->GetGlobalPos().x + m_Width * 0.5f, player->GetGlobalPos().y + m_Height * 0.5f };

	m_pLevelRef->PositionToIndex(pos, column, row);
	auto cell = m_pLevelRef->m_Grid[row][column];
	glm::vec2 cellCenter{ cell.boundingBox.x + cell.boundingBox.w / 2,cell.boundingBox.y + cell.boundingBox.h / 2 };


	if (*m_CurrentDirection == 0)
	{
		m_pLevelRef->GetDirectionFlags(row, column, m_AvailableDirection);
		if ((m_AvailableDirection & m_DirectionInput) == m_DirectionInput)
		{
			*m_CurrentDirection = m_DirectionInput;
		}
	}

	if (*m_CurrentDirection == CONNECTS_LEFT && pos.x < cellCenter.x ||
		*m_CurrentDirection == CONNECTS_RIGHT && pos.x > cellCenter.x ||
		*m_CurrentDirection == CONNECTS_UP && pos.y < cellCenter.y ||
		*m_CurrentDirection == CONNECTS_DOWN && pos.y > cellCenter.y)
	{
		//player->SetPosition(cellCenter.x - m_Width*0.5f, cellCenter.y- m_Height*0.5f, 0);
		m_pLevelRef->GetDirectionFlags(row, column, m_AvailableDirection);
		if ((m_AvailableDirection & m_DirectionInput) != m_DirectionInput)
		{
			*m_CurrentDirection = 0;
		}
		else *m_CurrentDirection = m_DirectionInput;
	}
}

void PlayerPhysicsComponent::Update(const float  deltaTime)
{
	int row{};
	int column{};

	float halfWidth{ m_pMoveCommand->m_Width * 0.5f };
	float halfHeight{ m_pMoveCommand->m_Height * 0.5f };

	glm::vec2 centerPos{ m_GameObject->GetGlobalPos().x + halfWidth, m_GameObject->GetGlobalPos().y + halfHeight * 0.5f };

	m_pLevelRef->PositionToIndex(centerPos, column, row);
	auto cell = m_pLevelRef->m_Grid[row][column];
	glm::vec2 cellCenter{ cell.boundingBox.x + cell.boundingBox.w / 2,cell.boundingBox.y + cell.boundingBox.h / 2 };
	int availableDirection{};

	if (m_CurrentDirection == CONNECTS_LEFT && centerPos.x < cellCenter.x ||
		m_CurrentDirection == CONNECTS_RIGHT && centerPos.x > cellCenter.x ||
		m_CurrentDirection == CONNECTS_UP && centerPos.y < cellCenter.y ||
		m_CurrentDirection == CONNECTS_DOWN && centerPos.y > cellCenter.y)
	{
		//player->SetPosition(cellCenter.x - m_Width*0.5f, cellCenter.y- m_Height*0.5f, 0);
		m_pLevelRef->GetDirectionFlags(row, column, availableDirection);
		if ((availableDirection & m_CurrentDirection) != m_CurrentDirection)
		{
			m_CurrentDirection = 0;
		}
	}


	Move(deltaTime);
}

PlayerPhysicsComponent::PlayerPhysicsComponent(dae::GameObject* go)
	:Physics(go)
{
	m_pMoveCommand = new MoveCommand(m_GameObject);
	SDL_GetWindowSize(dae::Renderer::GetInstance().get_window(), &m_WindowWidth, &m_WindowHeight);
}

PlayerPhysicsComponent::~PlayerPhysicsComponent()
{
	delete m_pMoveCommand;
	m_pMoveCommand = nullptr;

	delete m_pMoveUpCommand;
	m_pMoveUpCommand = nullptr;

	delete m_pMoveDownCommand;
	m_pMoveDownCommand = nullptr;

	delete m_pMoveLeftCommand;
	m_pMoveLeftCommand = nullptr;

	delete m_pMoveRightCommand;
	m_pMoveRightCommand = nullptr;
}

void PlayerPhysicsComponent::SetController(int playerIdx)
{
	auto pInputManager = &dae::InputManager::GetInstance();
	m_pMoveCommand->m_CurrentDirection = &m_CurrentDirection;
	pInputManager->GetController(playerIdx)->AddCommand(ControllerButton::LEFT_THUMB, KeyState::none, m_pMoveCommand);


	if(playerIdx == 0)
	{
		m_pMoveUpCommand = new MoveUpCommand(m_GameObject);
		m_pMoveUpCommand->m_CurrentDirection = &m_CurrentDirection;
		m_pMoveDownCommand = new MoveDownCommand(m_GameObject);
		m_pMoveDownCommand->m_CurrentDirection = &m_CurrentDirection;
		m_pMoveLeftCommand = new MoveLeftCommand(m_GameObject);
		m_pMoveLeftCommand->m_CurrentDirection = &m_CurrentDirection;
		m_pMoveRightCommand = new MoveRightCommand(m_GameObject);
		m_pMoveRightCommand->m_CurrentDirection = &m_CurrentDirection;

		pInputManager->GetKeyboard()->AddCommand(SDL_SCANCODE_W,KeyState::IsDown, m_pMoveUpCommand);
		pInputManager->GetKeyboard()->AddCommand(SDL_SCANCODE_S, KeyState::IsDown, m_pMoveDownCommand);
		pInputManager->GetKeyboard()->AddCommand(SDL_SCANCODE_A, KeyState::IsDown, m_pMoveLeftCommand);
		pInputManager->GetKeyboard()->AddCommand(SDL_SCANCODE_D, KeyState::IsDown, m_pMoveRightCommand);
	}
}

void PlayerPhysicsComponent::SetDimensions(int width, int height)
{
	m_Width = width;
	m_Height = height;
	m_pMoveCommand->m_Width = width;
	m_pMoveCommand->m_Height = height;
}

bool PlayerPhysicsComponent::GetIsDying()
{
	return m_pMoveCommand->m_IsDying;
}

void PlayerPhysicsComponent::SetIsDying(bool isDying)
{
	m_pMoveCommand->m_IsDying = isDying;
}

