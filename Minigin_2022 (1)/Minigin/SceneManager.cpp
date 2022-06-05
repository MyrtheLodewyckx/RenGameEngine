#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "EventManager.h"

void dae::SceneManager::Update(const float deltaTime)
{
	//Check if pause state is being changed
	auto e = dae::EventManager::GetEvent();
	if (e && e->ID == Events::GAME_PAUSE)
	m_IsPaused = !m_IsPaused;


	//Update all scene objects
	if(!m_IsPaused)
	for(auto& scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::Render() const
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}
