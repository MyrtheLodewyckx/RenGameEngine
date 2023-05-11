#include "SceneManager.h"
#include "Scene.h"

<<<<<<< Updated upstream
void dae::SceneManager::Update()
=======
void dae::SceneManager::Initialize()
{
	for (auto& scene : m_scenes)
	{
		scene->Initialize();
	}
}

void dae::SceneManager::Update(const float deltaTime)
>>>>>>> Stashed changes
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
