#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "EventManager.h"
#include "LevelManager.h"
#include "GamestateManager.h"
#include "GlobalValues.h"
#include "Victory.h"
#include "GameOver.h"

using namespace dae;


dae::Scene::Scene(int lvl)
	:m_Objects{}, m_Level{lvl}
{
}

Scene::~Scene() = default;


void dae::Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.emplace_back(object);
}

void Scene::Update(const float deltaTime)
{
	for(auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}

	auto e = dae::EventManager::GetInstance().GetEvent();
	if(e)
	switch (e->ID)
	{
	case Events::GAME_OVER:
	{
		auto gameOver = std::make_unique<GameOver>();
		dae::GameStateManager::GetInstance().Add(std::move(gameOver), 1);
	}
		break;
	case Events::RESTART_LEVEL:
	{
		auto scene = std::make_unique<dae::Scene>(1);
		dae::LevelManager::GetInstance().LoadLevel("lvl1.txt", *scene.get());
		dae::GameStateManager::GetInstance().Add(std::move(scene), 1);

		for (int i = 0; i < (int)GlobalValues::m_Scores.size(); ++i)
			GlobalValues::m_Scores[i] = 0;
	}
		break;
	case Events::NEXT_LEVEL:
	{
		if (m_Level == 1)
		{
			auto victory = std::make_unique<Victory>();
			dae::GameStateManager::GetInstance().Add(std::move(victory), 1);
		}
		else
		{
			auto scene = std::make_unique<dae::Scene>(++m_Level);
			std::string lvlFile = "lvl" + std::to_string(m_Level) + ".txt";
			dae::LevelManager::GetInstance().LoadLevel(lvlFile, *scene.get());
			dae::GameStateManager::GetInstance().Add(std::move(scene), 1);
		}
	}
		break;
	}



}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

