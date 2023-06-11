#include "FruitSpawner.h"

#include "Fruit.h"
#include "PacMan.h"
#include "GameObject.h"
#include "Scene.h"


void FruitSpawner::Update(const float)
{

	if(PacMan::GetPelletsEaten() >= m_NextAmtToBeEated )
	{
		const int amtInterval{ 50 };

		if (!Fruit::GetIsAlive())
		{
			auto go = std::make_shared<dae::GameObject>();
			go->AddComponent<TextureComponent>();
			go->AddComponent<Fruit>()->Initialize();
			go->SetPosition(270.f, 420.f, 0.f);
			dae::SceneManager::GetInstance().GetCurrentScene()->Add(go);
		}
		m_NextAmtToBeEated += amtInterval;
	}
}
