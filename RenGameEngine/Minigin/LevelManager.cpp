#include "MiniginPCH.h"
#include "LevelManager.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "PlayerPhysics.h"
#include "ladder.h"
#include "TextureComponent.h"
#include "Platform.h"
#include "BurgerPart.h"
#include <iostream>
#include <fstream>
#include <regex>
#include "Plate.h"
#include "HUDinfo.h"
#include "TextComponent.h"
#include "GameStateManager.h"
#include "AIPhysics.h"
#include "Player.h"


void dae::LevelManager::CreatePlayer(glm::vec3 pos, Scene& scene, int controllerIdx) const
{
	const float playerSize = 30.f;
	auto player = std::make_shared<GameObject>();
	auto spriteCom = player->AddComponent<SpriteComponent>();

	std::string texturePath = "sprites/Player" + std::to_string(controllerIdx + 1) + "WalkingForward.png";

	auto spriteTexture = ResourceManager::GetInstance().LoadTexture(texturePath);
	Sprite sprite{ spriteTexture, 1, 3, 0.5f };
	spriteCom->SetSprite(sprite, playerSize, 0);

	auto transformCom = player->AddComponent<Transform>();
	transformCom->SetPosition(pos);
	transformCom->SetDimentions(playerSize, playerSize);

	auto physics = player->AddComponent<PlayerPhysics>();
	physics->SetControllerIdx(controllerIdx);

	auto p = player->AddComponent<Player>();
	p->SetPlayerIdx(controllerIdx);

	scene.Add(player);
}

void dae::LevelManager::CreateEnemyPlayer(glm::vec3 pos, Scene& scene, int playerIdx) const
{
	const float playerSize = 30.f;
	auto enemy = std::make_shared<GameObject>();
	auto spriteCom = enemy->AddComponent<SpriteComponent>();

	std::string texturePath = "sprites/SausageWalkingForward.png";

	auto spriteTexture = ResourceManager::GetInstance().LoadTexture(texturePath);
	Sprite sprite{ spriteTexture, 1, 2, 0.25f };
	spriteCom->SetSprite(sprite, playerSize, 0);

	auto transformCom = enemy->AddComponent<Transform>();
	transformCom->SetPosition(pos);
	transformCom->SetDimentions(playerSize, playerSize);

	auto physics = enemy->AddComponent<PlayerPhysics>();
	physics->SetControllerIdx(playerIdx);

	auto e = enemy->AddComponent<Enemy>();
	e->SetEnemyID(EnemyID::Sausage);

	scene.Add(enemy);
}

std::shared_ptr<dae::GameObject> dae::LevelManager::CreateLadder(SDL_Rect hitbox, Scene& scene) const
{
	auto ladder = std::make_shared<GameObject>();

	auto transformCom = ladder->AddComponent<Transform>();
	transformCom->SetPosition((float)hitbox.x, (float)hitbox.y, 0);

	auto ladderCom = ladder->AddComponent<Ladder>();
	ladderCom->SetDimentions(hitbox.h, hitbox.w);

	auto textureCom = ladder->AddComponent<TextureComponent>();
	auto ladderTexture = ResourceManager::GetInstance().LoadTexture("LadderStep.png");
	textureCom->SetTexture(ladderTexture);
	textureCom->SetIsAlreadyRendered(true);

	scene.Add(ladder);

	return ladder;
}

std::shared_ptr<dae::GameObject> dae::LevelManager::CreatePlatform(SDL_Rect hitbox, Scene& scene) const
{
	auto platform = std::make_shared<GameObject>();

	auto transfCom = platform->AddComponent<Transform>();
	transfCom->SetPosition((float)hitbox.x, (float)hitbox.y, 0);

	auto textureCom = platform->AddComponent<TextureComponent>();
	auto platformTexture = ResourceManager::GetInstance().LoadTexture("Platform.png");
	textureCom->SetTexture(platformTexture);
	textureCom->SetIsAlreadyRendered(true);

	auto platformCom = platform->AddComponent<Platform>();
	platformCom->SetDimentions(hitbox.w, hitbox.h);

	scene.Add(platform);

	return platform;
}

std::shared_ptr<dae::GameObject> dae::LevelManager::CreatePlate(SDL_Rect hitbox, Scene& scene) const
{
	auto plate = std::make_shared<GameObject>();

	auto transfCom = plate->AddComponent<Transform>();
	transfCom->SetPosition((float)hitbox.x, (float)hitbox.y, 0);

	auto textureCom = plate->AddComponent<TextureComponent>();
	auto platformTexture = ResourceManager::GetInstance().LoadTexture("Plate.png");
	textureCom->SetTexture(platformTexture);
	textureCom->SetIsAlreadyRendered(true);

	auto platformCom = plate->AddComponent<Plate>();
	platformCom->SetDimentions(hitbox.w, hitbox.h);

	scene.Add(plate);

	return plate;
}

void dae::LevelManager::CreateHUD(glm::vec3 pos, int controllerIdx, Scene& scene)
{
	auto Hud = std::make_shared<GameObject>();
	auto info = Hud->AddComponent<HUD>();
	auto font = ResourceManager::GetInstance().LoadFont("pixel.otf", 20);


	info->SetPlayerIdx(controllerIdx);
	info->SetGlobalVariables(m_Lives[controllerIdx]);

	//TEXT COMPONENT
	auto HUDTextCom = Hud->AddComponent<TextComponent>();
	std::string sHUDtext = "LIVES: " + std::to_string(info->GetLives());

	HUDTextCom->SetFont(font);
	HUDTextCom->SetText(sHUDtext);

	//TRANSFORM COMPONENT
	auto sHUDTransformCom = Hud->AddComponent<Transform>();
	sHUDTransformCom->SetPosition(pos.x, pos.y + 50 * controllerIdx, pos.z);

	//TEXTURE COMPONENT
	Hud->AddComponent<TextureComponent>();

	scene.Add(Hud);

	//CHILD COMPONENT SCORE TEXT
	auto scoreHUD = std::make_shared<GameObject>();
	scoreHUD->SetParent(Hud.get());

	//TEXT COMPONENT
	auto scoreHUDTextCom = scoreHUD->AddComponent<TextComponent>();
	std::string scoreHUDtext = "SCORE: " + std::to_string(info->GetScore());

	scoreHUDTextCom->SetFont(font);
	scoreHUDTextCom->SetText(scoreHUDtext);

	//TRANSFORM COMPONENT
	auto scoreHUDTransformCom = scoreHUD->AddComponent<Transform>();
	scoreHUDTransformCom->SetPosition(pos.x + 300, pos.y + 50*controllerIdx, pos.z);

	//TEXTURE COMPONENT
	scoreHUD->AddComponent<TextureComponent>();

	scene.Add(scoreHUD);
}

std::shared_ptr<dae::GameObject> dae::LevelManager::CreateBurgerPart(SDL_Rect hitbox, std::string path, Scene& scene) const
{
	auto burger = std::make_shared<GameObject>();

	auto transfCom = burger->AddComponent<Transform>();
	transfCom->SetPosition((float)hitbox.x, (float)hitbox.y, 0);

	auto textureCom = burger->AddComponent<TextureComponent>();
	auto burgerTexture = ResourceManager::GetInstance().LoadTexture(path);
	textureCom->SetTexture(burgerTexture);
	textureCom->SetIsAlreadyRendered(true);


	auto burgerCom = burger->AddComponent<BurgerPart>();
	burgerCom->SetDimentions(hitbox.w, hitbox.h);

	scene.Add(burger);

	return burger;
}

void dae::LevelManager::CreateEnemy(SDL_Rect hitbox, Scene& scene, EnemyID id) const
{
	auto enemy = std::make_shared<GameObject>();
	enemy->AddComponent<SpriteComponent>();

	auto transformCom = enemy->AddComponent<Transform>();
	transformCom->SetPosition((float)hitbox.x, (float)hitbox.y, 0);
	transformCom->SetDimentions(float(hitbox.w), float(hitbox.h));

	enemy->AddComponent<AIPhysics>();

	auto e = enemy->AddComponent<Enemy>();
	e->SetEnemyID(id);

	scene.Add(enemy);
}


void dae::LevelManager::LoadLevel(const std::string& path, Scene& scene)
{
	std::regex info{ ".+\\(([0-9]+),([0-9]+)\\)\\(([0-9]+),([0-9]+)\\)" };

	std::string line; 
	std::smatch match;

	auto mode = dae::GameStateManager::GetInstance().GetGameMode();
	if ((mode == dae::GameMode::CoUp || mode == dae::GameMode::Versus) && m_Lives.size() == 1)
		m_Lives.emplace_back(3);
	else if (mode == dae::GameMode::SinglePlayer && m_Lives.size() == 2)
		m_Lives.pop_back();

	
	std::ifstream levelFile(path);
	if (levelFile.is_open())
	{
		while (getline(levelFile, line))
		{
			if (std::regex_search(line, match, info))
				switch (line[0])
				{
				case 'P':
					CreatePlatform(SDL_Rect(std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3]), std::stoi(match[4])), scene);
					break;
				case 'L':
					CreateLadder(SDL_Rect(std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3]), std::stoi(match[4])), scene);
					break;
				case 'F':
					CreatePlate(SDL_Rect(std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3]), std::stoi(match[4])), scene);
					break;
				case 'B':
				{
					switch (line[1])
					{
					case 'T':
						CreateBurgerPart(SDL_Rect(std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3]), std::stoi(match[4])), "sprites/bun.png", scene);
						break;
					case 'B':
						CreateBurgerPart(SDL_Rect(std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3]), std::stoi(match[4])), "sprites/bunBottom.png", scene);
						break;
					case 'C':
						CreateBurgerPart(SDL_Rect(std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3]), std::stoi(match[4])), "sprites/cheese.png", scene);
						break;
					case 'L':
						CreateBurgerPart(SDL_Rect(std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3]), std::stoi(match[4])), "sprites/lettuce.png", scene);
						break;
					case 'M':
						CreateBurgerPart(SDL_Rect(std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3]), std::stoi(match[4])), "sprites/meat.png", scene);
						break;
					}
					break;
				}
				case 'E':
					CreateEnemy(SDL_Rect(std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3]), std::stoi(match[4])), scene, EnemyID(line[1] - '0'));
					break;

//CREATE PLAYERS ACCORDING TO GAMEMODE
				case 'S':
				{
					switch (line[1])
					{
					case '1':
						if(mode == dae::GameMode::CoUp)
						CreatePlayer(glm::vec3(std::stoi(match[1]), std::stoi(match[2]), 0), scene, 0);
						break;
					case '2':
						if (mode == dae::GameMode::CoUp)
						CreatePlayer(glm::vec3(std::stoi(match[1]), std::stoi(match[2]), 0), scene, 1);
						break;
					case 'E':
						if (mode == dae::GameMode::Versus)
						CreateEnemyPlayer(glm::vec3(std::stoi(match[1]), std::stoi(match[2]), 0), scene, 1);
						break;
					default:
						if (mode == dae::GameMode::Versus || mode == dae::GameMode::SinglePlayer)
						CreatePlayer(glm::vec3(std::stoi(match[1]), std::stoi(match[2]), 0), scene, 0);
						break;
					}
					break;
				}
				}
		}
		levelFile.close();
	}

	for (int i = 0; i < (int)m_Lives.size(); ++i)
		CreateHUD(glm::vec3(20, 20, 0), i, scene);

}

dae::LevelManager::LevelManager()
{
}
