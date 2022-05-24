#include "MiniginPCH.h"
#include "PlayerPhysics.h"
#include "InputManager.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Movement.h"

std::vector<dae::PlayerPhysics*> dae::PlayerPhysics::m_ObjectList;

dae::PlayerPhysics::PlayerPhysics(GameObject* go) : Component(go) 
{
	m_ObjectList.push_back(this);
}

void dae::PlayerPhysics::Update(const float deltaTime)
{
	if (!m_pClimbingDownTexture)
	{
		m_pClimbingDownTexture = dae::ResourceManager::GetInstance().LoadTexture("sprites/Player" + std::to_string(m_ControllerIdx + 1) + "WalkingForward.png");
		m_pClimbingUpTexture = dae::ResourceManager::GetInstance().LoadTexture("sprites/Player" + std::to_string(m_ControllerIdx + 1) + "ClimbingUp.png");
		m_pWalkingTexture = dae::ResourceManager::GetInstance().LoadTexture("sprites/Player" + std::to_string(m_ControllerIdx + 1) + "WalkingSideways.png");
		m_Sprites[0].texturePtr = m_pClimbingDownTexture;
		m_Sprites[1].texturePtr = m_pWalkingTexture;
		m_Sprites[2].texturePtr = m_pClimbingUpTexture;
	}
	HandlePhysics(deltaTime);
}

void dae::PlayerPhysics::SetDimentions(float height, float width)
{
	m_Width = width;
	m_Height = height;
}

SDL_Rect dae::PlayerPhysics::GetHitBox()
{
	if (m_TransformPtr)
		return SDL_Rect((int)m_TransformPtr->GetPosition().x, (int)m_TransformPtr->GetPosition().y, (int)m_Width, (int)m_Height);
	else return SDL_Rect(0, 0, (int)m_Width, (int)m_Height);
}


glm::vec3 dae::PlayerPhysics::GetPos() const
{
	if (m_TransformPtr)
		return m_TransformPtr->GetPosition();
	else return glm::vec3(0, 0, 0);
}

void dae::PlayerPhysics::SetPos(glm::vec3 pos)
{
	m_TransformPtr->SetPosition(pos);
}

void dae::PlayerPhysics::HandlePhysics(const float deltaTime)
{
	const int horizontalSpeed{ 100 };
	const int verticalSpeed{ 60 };
	InputManager* is = &InputServiceLocator::get_input_system();
	Movement movement;

	auto j = is->GetJoystickDirection(m_ControllerIdx);

	if (!m_TransformPtr)
		m_TransformPtr = m_Go->GetComponent<Transform>();
	if (!m_Sprite)
		m_Sprite = m_Go->GetComponent<SpriteComponent>();

	switch (j)
	{
	case Direction::Right:
		if (m_IsOnGround)
		{
			movement.MoveHorizontally(deltaTime, horizontalSpeed, m_TransformPtr);
			m_Sprite->SetSprite(m_Sprites[1], m_Width, m_Height, SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
		}
		break;
	case Direction::Left:
		if (m_IsOnGround)
		{
			movement.MoveHorizontally(deltaTime, -horizontalSpeed, m_TransformPtr);
			m_Sprite->SetSprite(m_Sprites[1], m_Width, m_Height);
		}
		break;
	case Direction::Up:
		if (m_IsOnLadder)
		{
			movement.MoveVertically(deltaTime, verticalSpeed, m_TransformPtr);
			m_Sprite->SetSprite(m_Sprites[2], m_Width, m_Height);
		}
		break;
	case Direction::Down:
		if (m_IsOnLadder)
		{
			movement.MoveVertically(deltaTime, -verticalSpeed, m_TransformPtr);
			m_Sprite->SetSprite(m_Sprites[0], m_Width, m_Height);
		}
		break;
	}

}
