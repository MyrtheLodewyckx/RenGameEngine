#include <SceneManager.h>
#include "PacMan.h"

#include "Controller.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Pellet.h"
#include "PlayerPhysicsComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SpriteComponent.h"
#include "GeometryUtils.h"


void PacMan::Initialize()
{
	m_Sprite = m_GameObject->AddComponent<dae::SpriteComponent>();

	auto spriteTexture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PacMan_Sideways.png");
	dae::Sprite sprite{ spriteTexture, 1, 3, 0.1f };

	m_Sprite->SetSprite(sprite, 20.f, 20.f);

	auto controller = m_GameObject->AddComponent<Controller>();
	dae::InputManager::GetInstance().AddController(controller);

	m_GameObject->AddComponent<PlayerPhysicsComponent>();


	m_PelletsRef = dae::SceneManager::GetInstance().GetCurrentScene()->GetAllGameObjectsWithComponent<Pellet>();
}

void PacMan::CheckForPellets()
{
	for(const auto& pellet: m_PelletsRef)
	{
		glm::vec2 pos = m_GameObject->GetGlobalPos();
		if(GeoUtils::IsPointInRect(pellet->GetGlobalPos(),SDL_Rect(pos.x,pos.y,m_Sprite->GetWidth(),m_Sprite->GetHeight())))
		{
			
		}
	}
}

void PacMan::SetDimentions(int , int )
{
	//m_Sprite->Resize(width, height);
}

void PacMan::Update(const float)
{
	
}


