#include "SceneManager.h"

#include "InputManager.h"

void dae::SceneManager::Initialize()
{
	m_scenes.top()->Initialize();

	/*for (auto& scene : m_scenes)
	{
		scene->Initialize();
	}*/
}

void dae::SceneManager::Update(const float deltaTime)
{
	m_scenes.top()->Update(deltaTime);
	//for(auto& scene : m_scenes)
	//{
	//	scene->Update(deltaTime);
	//}
}

void dae::SceneManager::FixedUpdate(const float fixedTimeStep)
{
	m_scenes.top()->FixedUpdate(fixedTimeStep);
	/*for (auto& scene : m_scenes)
	{
		scene->FixedUpdate(fixedTimeStep);
	}*/
}

void dae::SceneManager::Render()
{
	m_scenes.top()->Render();
	/*for (const auto& scene : m_scenes)
	{
		scene->Render();
	}*/
}

void dae::SceneManager::PostRender() const
{
	m_scenes.top()->PostRender();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	return *scene;
}

void dae::SceneManager::Add(std::unique_ptr<Scene> toAdd, bool replace)
{
	m_add = true;
	m_newState = std::move(toAdd);
	m_replace = replace;
}

void dae::SceneManager::PopCurrent()
{
	m_remove = true;
}

void dae::SceneManager::ProcessStateChange()
{
	if (m_remove && !m_scenes.empty())
	{
		m_scenes.pop();

		if (!m_scenes.empty())
			m_scenes.top()->Start();

		m_remove = false;
	}

	if (m_add)
	{
		if (m_replace && !m_scenes.empty())
		{
			m_scenes.pop();
			m_replace = false;
		}

		if (!m_scenes.empty())
		{
			m_scenes.top()->Pause();
		}

		m_scenes.push(std::move(m_newState));
		m_scenes.top()->Initialize();
		m_add = false;
	}
}
