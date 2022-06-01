#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "EventManager.h"
#include "LevelManager.h"
#include "GamestateManager.h"

using namespace dae;


dae::Scene::Scene()
	:m_Objects{}
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
	case Events::RESTART_LEVEL:
		auto scene = std::make_unique<dae::Scene>();
		dae::LevelManager::GetInstance().LoadLevel("lvl1.txt", *scene.get());
		dae::GameStateManager::GetInstance().Add(std::move(scene), 1);
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

