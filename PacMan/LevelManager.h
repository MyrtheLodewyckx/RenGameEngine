#pragma once
#include <SDL_rect.h>

#include "Singleton.h"
#include "Scene.h"
#include <vector>
#include <glm/vec2.hpp>

#define CONNECTS_UP 1
#define CONNECTS_RIGHT 2
#define CONNECTS_DOWN 4
#define CONNECTS_LEFT 8
#define CONNECTS_ALL (CONNECTS_UP | CONNECTS_RIGHT | CONNECTS_DOWN | CONNECTS_LEFT)

inline bool CompareColor(SDL_Color color1, SDL_Color color2)
{
	if (color1.r == color2.r && color1.g == color2.g && color1.b == color2.b)
		return true;

	return false;
}

struct Cell
{
	Cell(int left, int top, int width, int height);

	SDL_Rect GetRectPoints() const;
	SDL_Rect boundingBox;
	bool m_IsPath{ false };
};

namespace dae
{
	class GameState;

	class LevelManager : public Singleton<LevelManager>
	{

		int m_NrOfRows;
		int m_NrOfCols;

		std::shared_ptr<GameObject> m_pPacManInstanceGO{};

		float m_CellWidth;
		float m_CellHeight;

		void CreatePlayer(glm::vec3 pos, Scene& scene, int playerIdx) const;
		void CreateEnemyPlayer(glm::vec3 pos, Scene& scene) const;
		void CreatePellet(glm::vec3 pos, Scene& scene) const;
		void CreateSuperPellet(glm::vec3 pos, Scene& scene) const;
		void CreateHUD(glm::vec3 pos, int controllerIdx, Scene& scene);
		void CreateEnemy(glm::vec3 pos, Scene& scene);

	public:

		std::vector<std::vector<Cell>> m_Grid{};

		void PositionToIndex(const glm::vec2 pos, int &column, int &row) const;
		void GetDirectionFlags(const glm::vec2 pos, int &direction) const;
		void GetDirectionFlags(int row, int column, int& direction) const;
		void LoadLevel(int lvl, Scene &scene);
		Cell* GetTo(const glm::vec2 pos, int& direction);
		Cell* GetFrom(const glm::vec2 pos, int& direction);


		LevelManager();
		~LevelManager() = default;
	};
}