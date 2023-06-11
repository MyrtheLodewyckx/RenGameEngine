#include "EnemyManager.h"

#include "ClydeMovements.h"
#include "InkyMovements.h"
#include "PacManInstance.h"
#include "PlayerPhysicsComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Ghosts/BlinkyMovements.h"


EnemyManager::EnemyManager(dae::GameObject* go)
	:Component(go)
{

}

void EnemyManager::Update(const float deltaTime)
{

	m_Timer += deltaTime;

	if(m_Timer >= 10.f)
	{
		m_Timer = 0;
		for(int i{0}; i < (int)m_GhostsObj.size(); ++i)
		{
			if(!m_Ghosts[i]->GetIsFree())
			{
				m_Ghosts[i]->SetFree(true);
				m_GhostsObj[i]->SetPosition(m_SpawnPos);
				break;
			}
		}
	}
}

void EnemyManager::Initialize()
{
	float width = 20.f;
	float height = 20.f;
	glm::vec3 pos{ 280,370, 0 };
	//auto scene = &;

	//CREATE BLINKY
	
		auto go = std::make_shared<dae::GameObject>();

		auto ghost = go->AddComponent<Ghost>();

		auto spriteTexture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/Ghosts/Blinky_Sideways.png");
		dae::Sprite side = { spriteTexture, 1, 2, 0.3f };

		spriteTexture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/Ghosts/Blinky_Vertical.png");
		dae::Sprite vertical = { spriteTexture, 1, 2, 0.3f };

		ghost->SetSprites(vertical, side);
		ghost->SetDimentions(width, height);

		if (PacManInstance::GetMode() != mode::versus)
		{
		auto movementComponent = go->AddComponent<BlinkyMovement>();
		movementComponent->SetDimensions((int)width, (int)height);
		}
		else
		{
			auto movementComponent = go->AddComponent<PlayerPhysicsComponent>();
			movementComponent->SetDimensions((int)width, (int)height);
			movementComponent->SetController(1);
		}

		go->SetPosition(pos);
		go->Initialize();
		dae::SceneManager::GetInstance().GetCurrentScene()->Add(go);

		m_GhostsObj.emplace_back(go.get());
		m_Ghosts.emplace_back(ghost.get());

	

	//CREATE INKY
	go = std::make_shared<dae::GameObject>();

	ghost = go->AddComponent<Ghost>();

	spriteTexture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/Ghosts/Inky_Sideways.png");
	side = { spriteTexture, 1, 2, 0.3f };

	spriteTexture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/Ghosts/Inky_Vertical.png");
	vertical = { spriteTexture, 1, 2, 0.3f };

	ghost->SetSprites(vertical, side);
	ghost->SetDimentions(width, height);

	auto movementComponent = go->AddComponent<InkyMovement>();
	movementComponent->SetDimensions((int)width, (int)height);

	go->SetPosition(pos);
	go->Initialize();
	dae::SceneManager::GetInstance().GetCurrentScene()->Add(go);

	m_GhostsObj.emplace_back(go.get());
	m_Ghosts.emplace_back(ghost.get());


	//CREATE PINKY
	go = std::make_shared<dae::GameObject>();

	ghost = go->AddComponent<Ghost>();

	spriteTexture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/Ghosts/Pinky_Sideways.png");
	side = { spriteTexture, 1, 2, 0.3f };

	spriteTexture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/Ghosts/Pinky_Vertical.png");
	vertical = { spriteTexture, 1, 2, 0.3f };

	ghost->SetSprites(vertical, side);
	ghost->SetDimentions(width, height);

	movementComponent = go->AddComponent<InkyMovement>();
	movementComponent->SetDimensions((int)width, (int)height);

	go->SetPosition(pos);
	go->Initialize();
	dae::SceneManager::GetInstance().GetCurrentScene()->Add(go);

	m_GhostsObj.emplace_back(go.get());
	m_Ghosts.emplace_back(ghost.get());

	//CREATE CLYDE
	go = std::make_shared<dae::GameObject>();

	ghost = go->AddComponent<Ghost>();

	spriteTexture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/Ghosts/Clyde_Sideways.png");
	side = { spriteTexture, 1, 2, 0.3f };

	spriteTexture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/Ghosts/Clyde_Vertical.png");
	vertical = { spriteTexture, 1, 2, 0.3f };

	ghost->SetSprites(vertical, side);
	ghost->SetDimentions(width, height);

	auto clydeMovementComponent = go->AddComponent<ClydeMovement>();
	clydeMovementComponent->SetDimensions((int)width, (int)height);

	go->SetPosition(pos);
	go->Initialize();
	dae::SceneManager::GetInstance().GetCurrentScene()->Add(go);

	m_GhostsObj.emplace_back(go.get());
	m_Ghosts.emplace_back(ghost.get());
}

void EnemyManager::SetSpawnPosition(glm::vec3 pos)
{
	m_SpawnPos = pos;
}
