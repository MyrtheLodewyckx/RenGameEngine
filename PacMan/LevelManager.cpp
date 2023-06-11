#include "LevelManager.h"

#include <iostream>

#include "EnemyManager.h"
#include "FruitSpawner.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"
#include "TextureComponent.h"

#include "GeometryUtils.h"
#include "HUD.h"
#include "PacMan.h"
#include "Pellet.h"
#include "PlayerPhysicsComponent.h"
#include "Renderer.h"
#include "SurfaceTexture2D.h"
#include "Ghosts/BlinkyMovements.h"
#include "Ghosts/Ghost.h"
#include "PacManInstance.h"

void dae::LevelManager::CreatePlayer(glm::vec3 pos, Scene& scene, int playerIdx) const
{
	int width{ 20};
	int height{ 20 };

	auto go = std::make_shared<dae::GameObject>();

	dae::Sprite sideways{};
	dae::Sprite vertical{};
	dae::Sprite dying{};


	if (playerIdx == 0)
	{
		auto spriteTexture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PacMan_Sideways.png");
		sideways = { spriteTexture, 1, 3, 0.1f };

		spriteTexture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PacMan_Vertical.png");
		vertical= { spriteTexture, 1, 3, 0.1f };

		spriteTexture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PacMan_Death.png");
		dying = { spriteTexture, 1, 11, 0.3f };
	}
	else
	{
		auto spriteTexture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/MsPacMan_Sideways.png");
		sideways = { spriteTexture, 1, 3, 0.1f };

		spriteTexture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/MsPacMan_Up.png");
		vertical = { spriteTexture, 1, 3, 0.1f };

		spriteTexture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PacMan_Death.png");
		dying = { spriteTexture, 1, 11, 0.3f };
	}

	go->AddComponent<SpriteComponent>()->SetSprite(sideways,(float)width,(float)height);

	auto pacman = go->AddComponent<PacMan>();
	pacman->SetSprites(sideways, vertical, dying);
	pacman->SetDimentions(width, height);
	go->SetPosition(pos);

	auto physics= go->AddComponent<PlayerPhysicsComponent>();
	physics->SetDimensions(width, height);
	physics->SetController(playerIdx);
	scene.Add(go);
}

void dae::LevelManager::CreateEnemyPlayer(glm::vec3 pos, Scene& scene) const
{
	float width = 20.f;
	float height = 20.f;
	auto go = std::make_shared<dae::GameObject>();

	auto ghost = go->AddComponent<Ghost>();

	auto spriteTexture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/Ghosts/Blinky_Sideways.png");
	Sprite side = { spriteTexture, 1, 2, 0.3f };

	spriteTexture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/Ghosts/Blinky_Vertical.png");
	Sprite vertical = { spriteTexture, 1, 2, 1.f };

	ghost->SetSprites(vertical, side);
	ghost->SetDimentions(width, height);


	auto movementComponent = go->AddComponent<PlayerPhysicsComponent>();
	movementComponent->SetDimensions((int)width, (int)height);
	movementComponent->SetController(1);

	go->SetPosition(pos);

	scene.Add(go);
}

void dae::LevelManager::CreatePellet(glm::vec3 pos, Scene& scene) const
{
	auto go = std::make_shared<dae::GameObject>();

	go->AddComponent<Pellet>();
	auto textureComponent = go->AddComponent<TextureComponent>();
	auto texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/Pellet.png");
	textureComponent->SetTexture(texture);
	
	go->SetPosition(pos.x - texture->GetSize().x * 0.5f, pos.y - texture->GetSize().y * 0.5f, 0);

	scene.Add(go);
}

void dae::LevelManager::CreateSuperPellet(glm::vec3 pos, Scene& scene) const
{
	auto go = std::make_shared<dae::GameObject>();

	auto pellet = go->AddComponent<Pellet>();
	pellet->m_Amt = 50;
	auto textureComponent = go->AddComponent<TextureComponent>();
	auto texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/SuperPellet.png");
	textureComponent->SetTexture(texture);
	go->SetPosition(pos.x - texture->GetSize().x*0.5f, pos.y - texture->GetSize().y * 0.5f,0);

	scene.Add(go);
}

void dae::LevelManager::CreateHUD(glm::vec3, int, Scene& scene)
{
	auto go = std::make_shared<GameObject>();
	auto hud = go->AddComponent<HUD>();
	scene.Add(go);

	auto goScoreText = std::make_shared<GameObject>();
	goScoreText->AddComponent<TextureComponent>();
	auto text = goScoreText->AddComponent<textComponent>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Fonts/pixel.otf", 20);
	text->SetFont(font);
	text->SetText("Score :" + std::to_string(gScore));
	text->SetColor(SDL_Color{ 255,255,255,255 });
	hud->SetScoreTextComp(text);

	goScoreText->SetPosition(10, 10, 0);
	goScoreText->SetParent(go);
	scene.Add(goScoreText);
}

void dae::LevelManager::CreateEnemy(glm::vec3 pos, Scene& scene)
{
	float width = 20.f;
	float height = 20.f;
	auto go = std::make_shared<dae::GameObject>();

	auto ghost = go->AddComponent<Ghost>();

	auto spriteTexture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/Ghosts/Blinky_Sideways.png");
	Sprite side = { spriteTexture, 1, 2, 0.3f };

	spriteTexture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/Ghosts/Blinky_Vertical.png");
	Sprite vertical = { spriteTexture, 1, 2, 0.3f };

	ghost->SetSprites(vertical, side);
	ghost->SetDimentions(width, height);


	auto movementComponent = go->AddComponent<BlinkyMovement>();
	movementComponent->SetDimensions((int)width, (int)height);

	go->SetPosition(pos);

	scene.Add(go);
}


void dae::LevelManager::PositionToIndex(const glm::vec2 pos, int& column, int& row) const
{
	//COLUMN
	for (int i = 0; i < m_NrOfCols; ++i)
	{
		if ((i + 1) * m_CellWidth > pos.x)
		{
			column = i;
			break;
		}
	}

	//ROW
	for (int i = 0; i < m_NrOfRows; ++i)
	{
		if ((i + 1) * m_CellHeight > pos.y)
		{
			row = i;
			break;
		}
	}
}

void dae::LevelManager::GetDirectionFlags(const glm::vec2 pos, int& direction) const
{
	int row{};
	int column{};
	PositionToIndex(pos,column,row);

	GetDirectionFlags(row, column, direction);

}


void dae::LevelManager::GetDirectionFlags(int row, int column, int& direction) const
{
	direction = 0;

	int up = unsigned(row - 1) % m_NrOfRows;

	if (m_Grid[up][column].m_IsPath)
		direction |= CONNECTS_UP;

	int down = (row + 1) % m_NrOfRows;

	if (m_Grid[down][column].m_IsPath)
		direction |= CONNECTS_DOWN;

	int left = unsigned(column - 1) % m_NrOfCols;

	if (m_Grid[row][left].m_IsPath)
		direction |= CONNECTS_LEFT;

	int right = (column + 1) % m_NrOfCols;

	if (m_Grid[row][right].m_IsPath)
		direction |= CONNECTS_RIGHT;
}

void dae::LevelManager::LoadLevel(int lvl, Scene& scene)
{
	int windowWidth{};
	int windowHeight{};
	SDL_GetWindowSize(Renderer::GetInstance().get_window(), &windowWidth, &windowHeight);

 

	Sprite backGroundSprite { ResourceManager::GetInstance().LoadTexture("Levels/Level" + std::to_string(lvl) + "s.png") ,1,1,0.2f };
	auto state = m_pPacManInstanceGO->GetComponent<PacManInstance>();
	state->SetBackGround(backGroundSprite, windowWidth, windowHeight);
	std::string path{ "Levels/Level" + std::to_string(lvl) + "_g.png"};

	auto go = std::make_shared<GameObject>();
	go->AddComponent<FruitSpawner>();
	scene.Add(go);

	scene.Add(m_pPacManInstanceGO);

	go = std::make_shared<GameObject>();
	auto enemySpawner = go->AddComponent<EnemyManager>();
	scene.Add(go);


	auto map = ResourceManager::GetInstance().LoadSurface(path);
	auto texSize = map->GetSize();
	m_NrOfCols = (int)texSize.x;
	m_NrOfRows = (int)texSize.y;

	m_CellWidth = { float(windowWidth / m_NrOfCols) };
	m_CellHeight = { float(windowHeight / m_NrOfRows) };
	if (!m_Grid.empty())
		m_Grid.clear();

	m_Grid.resize(m_NrOfRows);

	for (int y{ 0 }; y < texSize.y; ++y)
	{
		for (int x{ 0 }; x < texSize.x; ++x)
		{
			m_Grid[y].emplace_back(x * (int)m_CellWidth, y * (int)m_CellHeight, (int)m_CellWidth, (int)m_CellHeight);
			auto pixel = map->Sample(x, y);

			if (CompareColor(pixel, SDL_Color{255,255,255}))
			{
				if(PacManInstance::GetMode() == mode::co_up)
				{
					CreatePlayer({ x * (m_CellWidth-1) + m_CellWidth * 0.5f, y * m_CellHeight + m_CellHeight * 0.25f, 0.f }, scene, 0);
					m_Grid[y].back().m_IsPath = true;

					++x;
					CreatePlayer({ x * m_CellWidth + m_CellWidth * 0.5f, y * m_CellHeight + m_CellHeight * 0.25f, 0.f }, scene, 1);
					m_Grid[y].emplace_back(x * (int)m_CellWidth, y * (int)m_CellHeight, (int)m_CellWidth, (int)m_CellHeight);
					m_Grid[y].back().m_IsPath = true;
				}
				else
				{
					CreatePlayer({ x * m_CellWidth + m_CellWidth * 0.5f, y * m_CellHeight + m_CellHeight * 0.25f, 0.f }, scene, 0);
					m_Grid[y].back().m_IsPath = true;

					++x;
					m_Grid[y].emplace_back(x * (int)m_CellWidth, y * (int)m_CellHeight, (int)m_CellWidth, (int)m_CellHeight);
					m_Grid[y].back().m_IsPath = true;
				}
			}
			else if (CompareColor(pixel, SDL_Color{ 255,0,0 }))
			{
				CreatePellet({ x * m_CellWidth + m_CellWidth * 0.5f,y * m_CellHeight + m_CellHeight * 0.5f,0.f }, scene);
				m_Grid[y].back().m_IsPath = true;
			}
			else if (CompareColor(pixel, SDL_Color{ 0,0,255 }))
			{
				CreateSuperPellet({ x * m_CellWidth + m_CellWidth * 0.5f,y * m_CellHeight + m_CellHeight * 0.5f,0.f }, scene);
				m_Grid[y].back().m_IsPath = true;
			}
			else if (CompareColor(pixel, SDL_Color{ 0,255,0}) || CompareColor(pixel,{255,0,255}))
			{
				m_Grid[y].back().m_IsPath = true;
			}
			else if(CompareColor(pixel, SDL_Color{ 255,255,0 }))
			{
				m_Grid[y].back().m_IsPath = true;
				enemySpawner->SetSpawnPosition({ x * m_CellWidth + m_CellWidth * 0.5f, y * m_CellHeight + m_CellHeight * 0.25f, 0.f });
			}
		}
		std::cout << '\n';
	}

	CreateHUD({}, 0, scene);
}

Cell* dae::LevelManager::GetTo(const glm::vec2 pos, int& direction)
{
	int row{}, column{};
	PositionToIndex(pos, column, row);

	if ((direction & CONNECTS_LEFT) == CONNECTS_LEFT)
	{
		--column;
		if (column < 0)
			column = 0;
	}
	else if ((direction & CONNECTS_RIGHT) == CONNECTS_RIGHT)
	{
		++column;
		if (column >= m_NrOfCols)
			column = m_NrOfCols -1;
	}
	if ((direction & CONNECTS_UP) == CONNECTS_UP)
	{
		--row;
		if (row < 0)
			row = 0;
	}
	else if ((direction & CONNECTS_DOWN) == CONNECTS_DOWN)
	{
		++row;
		if (row >= m_NrOfRows)
			row = m_NrOfRows - 1;
	}


	return &m_Grid[row][column];
}

Cell* dae::LevelManager::GetFrom(const glm::vec2 pos, int& direction)
{
	int row{}, column{};
	PositionToIndex(pos, column, row);

	if ((direction & CONNECTS_LEFT) == CONNECTS_LEFT)
		++column;
	else if ((direction & CONNECTS_RIGHT) == CONNECTS_RIGHT)
		--column;

	if ((direction & CONNECTS_UP) == CONNECTS_UP)
		++row;
	else if ((direction & CONNECTS_DOWN) == CONNECTS_DOWN)
		--row;

	if (row < 0 || row >= m_NrOfRows || column < 0 || column >= m_NrOfCols)
		return nullptr;

	return &m_Grid[row][column];
}

dae::LevelManager::LevelManager()
{
	m_pPacManInstanceGO = std::make_shared<GameObject>();
	m_pPacManInstanceGO->AddComponent<PacManInstance>();
	m_pPacManInstanceGO->AddComponent<SpriteComponent>();
	m_pPacManInstanceGO->Initialize();
}

Cell::Cell(int left, int top, int width, int height)
	:boundingBox{left,top,width,height}
{
}

SDL_Rect Cell::GetRectPoints() const
{
	return boundingBox;
}
