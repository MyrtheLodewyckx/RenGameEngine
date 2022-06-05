#pragma once
#include "Singleton.h"
#include <string>
#include "SceneManager.h"
#include "Scene.h"
#include "Enemy.h"
#include <vector>

namespace dae
{
	class LevelManager : public Singleton<LevelManager>
	{
		void CreatePlayer(glm::vec3 pos, Scene& scene, int playerIdx) const;
		void CreateEnemyPlayer(glm::vec3 pos, Scene& scene, int playerIdx) const;
		std::shared_ptr<GameObject> CreateLadder(SDL_Rect hitbox, Scene& scene) const;
		std::shared_ptr<GameObject> CreatePlatform(SDL_Rect hitbox, Scene& scene) const;
		std::shared_ptr<GameObject> CreatePlate(SDL_Rect hitbox, Scene& scene) const;
		std::shared_ptr<GameObject> CreateBurgerPart(SDL_Rect hitbox, std::string path, Scene& scene) const;
		void CreateEnemy(SDL_Rect hitbox, Scene& scene, EnemyID id) const;
		void CreateHUD(glm::vec3 pos, int controllerIdx, Scene& scene);
	

	public:
		void LoadLevel(const std::string& path, Scene& scene);
		LevelManager();
		~LevelManager()=default;
	};
}