#include "PlayerPhysicsComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Controller.h"

void MoveCommand::Execute(float x, float y, const float deltaTime)
{
	glm::vec3 dir{x,y,0};
	dir /= dir.length();
	dir *= m_Speed * deltaTime/1000.f;

	auto pos = player->GetGlobalPos() + glm::vec3{dir.x, -dir.y, dir.z};
	player->SetPosition(pos.x,pos.y,pos.z);
}

void MoveCommand::SetSpeed(float speed)
{
	m_Speed = speed;
} 

PlayerPhysicsComponent::PlayerPhysicsComponent(dae::GameObject* go)
	:Component(go)
{
	auto pMoveCommand = new MoveCommand(m_GameObject);
	go->GetComponent<Controller>()->AddCommand(ControllerButton::LEFT_THUMB,KeyState::none, pMoveCommand);
}

