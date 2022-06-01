#include "MiniginPCH.h"
#include "BurgerPart.h"
#include "PlayerPhysics.h"
#include "Events.h"
#include "EventManager.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Platform.h"
#include "Renderer.h"
#include "Plate.h"
#include "Collision.h"

std::vector<dae::BurgerPart*> dae::BurgerPart::m_ObjectList;

dae::BurgerPart::BurgerPart(GameObject* go)
	:Component(go)
{
	m_ObjectList.emplace_back(this);
}

dae::BurgerPart::~BurgerPart()
{
	auto newEnd = std::remove(m_ObjectList.begin(), m_ObjectList.end(), this);
	m_ObjectList.erase(newEnd, m_ObjectList.end());
}

void dae::BurgerPart::Update(const float deltaTime)
{
	//MAKE SURE EVERYTHING IS INITIALIZED
	auto players = PlayerPhysics::GetAllInstances();

	if (!m_TransformPtr)
		m_TransformPtr = m_Go->GetComponent<Transform>();

	if (!m_texturePtr)
		m_texturePtr = m_Go->GetComponent<TextureComponent>();

	if (m_EnterPoints.size() != players.size())
		m_EnterPoints.resize(players.size());

	//CHECK FOR ALL PLAYERS
	for (int i = 0; i < players.size(); ++i)
	{
		//Get first enterpoint
		if (Collision::IsOverlapping(SDL_Rect((int)m_TransformPtr->GetPosition().x, (int)m_TransformPtr->GetPosition().y, m_Width, m_Height), players[i]->GetHitBox()) && m_EnterPoints[i] == 0)
			m_EnterPoints[i] = players[i]->GetHitBox().x + players[i]->GetHitBox().w / 2;
		
	//Refresh enterpoint on exit
		else if(!Collision::IsOverlapping(SDL_Rect((int)m_TransformPtr->GetPosition().x, (int)m_TransformPtr->GetPosition().y, m_Width, m_Height), players[i]->GetHitBox()))
			m_EnterPoints[i] = 0;
	}

	for (int i = 0; i < m_EnterPoints.size(); ++i)
	{
		if (m_EnterPoints[i] != 0)
		{
			if (m_EnterPoints[i] > m_TransformPtr->GetPosition().x + m_Width / 2 && players[i]->GetPos().x < m_TransformPtr->GetPosition().x)
			{
				
				m_IsFalling = true;
				m_EnterPoints[i] = 0;
				ScoreChangeEvent* e = new ScoreChangeEvent{};
				e->amt = 50;
				e->controllerIdx = players[i]->GetControllerIdx();
				dae::EventManager::GetInstance().AddEvent(e);

			}
			else if (m_EnterPoints[i] < m_TransformPtr->GetPosition().x + m_Width / 2 && players[i]->GetPos().x > m_TransformPtr->GetPosition().x + m_Width)
			{

				m_IsFalling = true;
				m_EnterPoints[i] = 0;
				ScoreChangeEvent* e = new ScoreChangeEvent{};
				e->amt = 50;
				e->controllerIdx = players[i]->GetControllerIdx();
				dae::EventManager::GetInstance().AddEvent(e);

			}

		}

		if (m_IsFalling)
			Fall(deltaTime);
	}

}

void dae::BurgerPart::Render() const
{
	if(m_TransformPtr)
	Renderer::GetInstance().RenderTexture(*m_texturePtr->GetTexture().get(), m_TransformPtr->GetPosition().x, m_TransformPtr->GetPosition().y, (float)m_Width, (float)m_Height);
}

void dae::BurgerPart::SetDimentions(int width, int height)
{
	m_Width = width;
	m_Height = height;
}

void dae::BurgerPart::Fall(const float deltaTime)
{
	m_TransformPtr->SetPosition(m_TransformPtr->GetPosition().x, m_TransformPtr->GetPosition().y + 50 * deltaTime,0);

	

	for (int i = 0; i < m_ObjectList.size(); ++i)
	{
		if (m_ObjectList[i]!= this && Collision::IsOverlapping(SDL_Rect((int)m_TransformPtr->GetPosition().x + m_Width / 4, (int)m_TransformPtr->GetPosition().y + m_Height, m_Width / 2, m_Height),
			SDL_Rect((int)m_ObjectList[i]->m_TransformPtr->GetPosition().x, (int)m_ObjectList[i]->m_TransformPtr->GetPosition().y + m_ObjectList[i]->m_Height, m_ObjectList[i]->m_Width, 1)))
		{
			if (m_ObjectList[i]->m_IsOnPlate)
			{
				m_IsOnPlate = true;
				m_TransformPtr->SetPosition(m_TransformPtr->GetPosition().x, (float)m_ObjectList[i]->m_TransformPtr->GetPosition().y - m_Height, 0);
			}
			else 
			m_ObjectList[i]->m_IsFalling = true;
		}
	}

	//Check if colliding with platform
	auto platforms = Platform::GetAllInstances();
	for (int i = 0; i < platforms.size(); ++i)
	{
		if (Collision::IsOverlapping(SDL_Rect((int)m_TransformPtr->GetPosition().x +m_Width/4, (int)m_TransformPtr->GetPosition().y + m_Height, m_Width /2, 1),
			SDL_Rect(platforms[i]->GetDimentions().x, platforms[i]->GetDimentions().y + platforms[i]->GetDimentions().h, platforms[i]->GetDimentions().w, 1)))
		{
			m_TransformPtr->SetPosition(m_TransformPtr->GetPosition().x, (float)platforms[i]->GetDimentions().y, 0);
			m_IsFalling = false;
		}
	}

	auto plates = Plate::GetAllInstances();
	for (int i = 0; i < plates.size(); ++i)
	{
		if (Collision::IsOverlapping(SDL_Rect((int)m_TransformPtr->GetPosition().x + m_Width / 4, (int)m_TransformPtr->GetPosition().y + m_Height, m_Width / 2, 1),
			SDL_Rect(plates[i]->GetDimentions().x, plates[i]->GetDimentions().y, plates[i]->GetDimentions().w, plates[i]->GetDimentions().h)))
		{
			m_TransformPtr->SetPosition(m_TransformPtr->GetPosition().x, (float)plates[i]->GetDimentions().y - m_Height, 0);
			m_IsOnPlate = true;
		}
	}
}
