#include "PlayerPhysicsComponent.h"

#include <iostream>

#include "GameObject.h"
#include "InputManager.h"
#include "Controller.h"
#include "Keyboard.h"
#include "Renderer.h"

static bool IsOpposite(int a, int b) {
	return (a == CONNECTS_LEFT && b == CONNECTS_RIGHT) ||
		(a == CONNECTS_RIGHT && b == CONNECTS_LEFT) ||
		(a == CONNECTS_UP && b == CONNECTS_DOWN) ||
		(a == CONNECTS_DOWN && b == CONNECTS_UP);
}


void MoveCommand::Execute(float x, float y, const float)
{
	if (fabsf(x) < 0.001f && fabsf(y) < 0.001f) return;

	if (fabsf(x) > fabsf(y))
		m_DirectionInput = (x < 0) ? CONNECTS_LEFT : CONNECTS_RIGHT;
	else
		m_DirectionInput = (y < 0) ? CONNECTS_DOWN : CONNECTS_UP;

	if (m_PendingDirection) *m_PendingDirection = m_DirectionInput;
}


void MoveUpCommand::Execute() { if (m_PendingDirection) *m_PendingDirection = CONNECTS_UP; }
void MoveDownCommand::Execute() { if (m_PendingDirection) *m_PendingDirection = CONNECTS_DOWN; }
void MoveLeftCommand::Execute() { if (m_PendingDirection) *m_PendingDirection = CONNECTS_LEFT; }
void MoveRightCommand::Execute() { if (m_PendingDirection) *m_PendingDirection = CONNECTS_RIGHT; }


void PlayerPhysicsComponent::Update(const float  deltaTime)
{
	if (m_IsDying) return;

	int row{}, column{};
	float halfWidth = m_pMoveCommand->m_Width * 0.5f;
	float halfHeight = m_pMoveCommand->m_Height * 0.5f;

	glm::vec2 centerPos{ m_GameObject->GetGlobalPos().x + halfWidth, m_GameObject->GetGlobalPos().y + halfHeight };

	m_pLevelRef->PositionToIndex(centerPos, column, row);
	const auto& cell = m_pLevelRef->m_Grid[row][column];
	glm::vec2 cellCenter{ cell.boundingBox.x + cell.boundingBox.w * 0.5f,
						  cell.boundingBox.y + cell.boundingBox.h * 0.5f };

	int availableDirection{};
	m_pLevelRef->GetDirectionFlags(row, column, availableDirection);

	// check passing/being at the center of the cell
	const bool crossedCenter =
		(m_CurrentDirection == CONNECTS_LEFT && centerPos.x < cellCenter.x) ||
		(m_CurrentDirection == CONNECTS_RIGHT && centerPos.x > cellCenter.x) ||
		(m_CurrentDirection == CONNECTS_UP && centerPos.y < cellCenter.y) ||
		(m_CurrentDirection == CONNECTS_DOWN && centerPos.y > cellCenter.y);

	// if the current path became invalid after the center, stop
	if (crossedCenter && ((availableDirection & m_CurrentDirection) != m_CurrentDirection))
		m_CurrentDirection = 0;

	if (m_PendingDirection != 0)
	{
		const bool canTakePending = ((availableDirection & m_PendingDirection) == m_PendingDirection);

		if (m_CurrentDirection == 0 || crossedCenter)
		{
			if (canTakePending)
			{
				m_CurrentDirection = m_PendingDirection;
			}
		}
		else if (IsOpposite(m_CurrentDirection, m_PendingDirection) && canTakePending)
		{
			m_CurrentDirection = m_PendingDirection;
			if (m_CurrentDirection == CONNECTS_LEFT || m_CurrentDirection == CONNECTS_RIGHT)
				m_GameObject->SetPosition(cellCenter.x - halfWidth, m_GameObject->GetGlobalPos().y, m_GameObject->GetGlobalPos().z);
			else
				m_GameObject->SetPosition(m_GameObject->GetGlobalPos().x, cellCenter.y - halfHeight, m_GameObject->GetGlobalPos().z);

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
	m_pMoveCommand->m_PendingDirection = &m_PendingDirection;
	pInputManager->GetController(playerIdx)->AddCommand(ControllerButton::LEFT_THUMB, KeyState::none, m_pMoveCommand);

	if (playerIdx == 0)
	{
		m_pMoveUpCommand = new MoveUpCommand(m_GameObject);
		m_pMoveDownCommand = new MoveDownCommand(m_GameObject);
		m_pMoveLeftCommand = new MoveLeftCommand(m_GameObject);
		m_pMoveRightCommand = new MoveRightCommand(m_GameObject);

		m_pMoveUpCommand->m_CurrentDirection = &m_CurrentDirection;
		m_pMoveDownCommand->m_CurrentDirection = &m_CurrentDirection;
		m_pMoveLeftCommand->m_CurrentDirection = &m_CurrentDirection;
		m_pMoveRightCommand->m_CurrentDirection = &m_CurrentDirection;

		m_pMoveUpCommand->m_PendingDirection = &m_PendingDirection;
		m_pMoveDownCommand->m_PendingDirection = &m_PendingDirection;
		m_pMoveLeftCommand->m_PendingDirection = &m_PendingDirection;
		m_pMoveRightCommand->m_PendingDirection = &m_PendingDirection;

		pInputManager->GetKeyboard()->AddCommand(SDL_SCANCODE_W, KeyState::IsPressed, m_pMoveUpCommand);
		pInputManager->GetKeyboard()->AddCommand(SDL_SCANCODE_S, KeyState::IsPressed, m_pMoveDownCommand);
		pInputManager->GetKeyboard()->AddCommand(SDL_SCANCODE_A, KeyState::IsPressed, m_pMoveLeftCommand);
		pInputManager->GetKeyboard()->AddCommand(SDL_SCANCODE_D, KeyState::IsPressed, m_pMoveRightCommand);
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
	return m_IsDying;
}

void PlayerPhysicsComponent::SetIsDying(bool isDying)
{
	m_IsDying = isDying;
}



