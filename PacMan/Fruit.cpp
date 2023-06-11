#include "Fruit.h"

#include "PacMan.h"
#include "PacManInstance.h"
#include "SceneManager.h"
#include <GeometryUtils.h>

#include "EventManager.h"
#include "PacManEvents.h"
#include "SoundSystem.h"

Fruit::~Fruit()
{
	m_IsAlive = false;
}

void Fruit::Initialize()
{
	m_IsAlive = true;
	m_pPacmanRef = dae::SceneManager::GetInstance().GetCurrentScene()->GetAllGameObjectsWithComponent<PacMan>();
	m_pTexture = m_GameObject->GetComponent<TextureComponent>();
	int size{ 20 };

	switch(PacManInstance::GetCurrentLevel())
	{
	case 1:
		m_pTexture->SetTexture("Fruits/Cherry.png", size, size);
	break;
	case 2:
		m_pTexture->SetTexture("Fruits/Strawberry.png", size, size);
		break;
	case 3:
		m_pTexture->SetTexture("Fruits/Orange.png", size, size);
		break;
	}
	m_PacSize = (int)m_pPacmanRef[0]->GetComponent<dae::SpriteComponent>()->GetWidth();
}

void Fruit::Update(float)
{
	for (int i{ 0 }; i < (int)m_pPacmanRef.size(); ++i)
	{
		if(GeoUtils::IsPointInRect({ m_pPacmanRef[i]->GetGlobalPos().x + m_PacSize * 0.5f,m_pPacmanRef[i]->GetGlobalPos().y + m_PacSize * 0.5f },
			SDL_Rect{ (int)m_GameObject->GetGlobalPos().x,(int)m_GameObject->GetGlobalPos().y,(int)m_pTexture->GetSize().x,(int)m_pTexture->GetSize().y }))
		{
			sound_system* a = &AudioServiceLocator::get_sound_system();
			a->Play(EAT_FRUIT, 50);
			auto scoreEvent = new SCORE_CHANGE();
			scoreEvent->amt = 300;
			dae::EventManager::GetInstance().AddEvent(scoreEvent);
			m_IsAlive = false;
			m_GameObject->remove();
		}
	}

}

bool Fruit::GetIsAlive()
{
	return m_IsAlive;
}
