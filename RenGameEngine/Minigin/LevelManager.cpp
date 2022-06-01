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
#include "Player.h"
#include "TextComponent.h"


void dae::LevelManager::CreatePlayer(glm::vec3 pos, Scene& scene, int controllerIdx) const
{
	const int playerSize = 30;
	auto player = std::make_shared<GameObject>();
	auto spriteCom = player->AddComponent<SpriteComponent>();

	std::string texturePath = "sprites/Player" + std::to_string(controllerIdx + 1) + "WalkingForward.png";

	auto spriteTexture = ResourceManager::GetInstance().LoadTexture(texturePath);
	Sprite sprite{ spriteTexture, 1, 3, 0.5f };
	spriteCom->SetSprite(sprite, playerSize, 0);

	auto transformCom = player->AddComponent<Transform>();
	transformCom->SetPosition(pos);

	auto physics = player->AddComponent<PlayerPhysics>();
	physics->SetControllerIdx(controllerIdx);
	physics->SetDimentions(playerSize, playerSize);

	scene.Add(player);
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

	//std::string texturePath = "sprites/Player" + std::to_string(controllerIdx + 1) + "WalkingForward.png";
	//auto spriteTexture = ResourceManager::GetInstance().LoadTexture(texturePath);
	//Sprite sprite{ nullptr, 1, 3, 0.5f };
	//spriteCom->SetSprite(sprite, playerSize, 0);

	auto transformCom = enemy->AddComponent<Transform>();
	transformCom->SetPosition((float)hitbox.x, (float)hitbox.y, 0);

	auto physics = enemy->AddComponent<Enemy>();
	physics->SetValues(id, hitbox.w, hitbox.h);

	scene.Add(enemy);
}

void dae::LevelManager::CreateHUD(glm::vec3 pos, Scene* scene, int controllerIdx) const
{
	auto HUD = std::make_shared<GameObject>();
	auto player = HUD->AddComponent<Player>();
	auto font = ResourceManager::GetInstance().LoadFont("pixel.otf", 20);


	player->SetControllerIdx(controllerIdx);

	//TEXT COMPONENT
	auto HUDTextCom = HUD->AddComponent<TextComponent>();
	std::string sHUDtext = "LIVES: " + std::to_string(player->GetLives());

	HUDTextCom->SetFont(font);
	HUDTextCom->SetText(sHUDtext);

	//TRANSFORM COMPONENT
	auto sHUDTransformCom = HUD->AddComponent<Transform>();
	sHUDTransformCom->SetPosition(pos);

	//TEXTURE COMPONENT
	HUD->AddComponent<TextureComponent>();

	scene->Add(HUD);

	//CHILD COMPONENT SCORE TEXT
	auto scoreHUD = std::make_shared<GameObject>();
	scoreHUD->SetParent(HUD.get());

	//TEXT COMPONENT
	auto scoreHUDTextCom = scoreHUD->AddComponent<TextComponent>();
	std::string scoreHUDtext = "SCORE: " + std::to_string(player->GetScore());

	scoreHUDTextCom->SetFont(font);
	scoreHUDTextCom->SetText(scoreHUDtext);

	//TRANSFORM COMPONENT
	auto scoreHUDTransformCom = scoreHUD->AddComponent<Transform>();
	scoreHUDTransformCom->SetPosition(pos.x + 300, pos.y, pos.z);

	//TEXTURE COMPONENT
	scoreHUD->AddComponent<TextureComponent>();

	scene->Add(scoreHUD);
}

void dae::LevelManager::LoadLevel(const std::string& path, Scene& scene)
{
	std::regex info{ ".+\\(([0-9]+),([0-9]+)\\)\\(([0-9]+),([0-9]+)\\)" };


	std::string line; 
	std::smatch match;
	
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
				}
		}
		levelFile.close();

		CreatePlayer(glm::vec3(240, 599, 0), scene, 0);
		CreateHUD(glm::vec3(100, 10, 0), &scene, 0);
	}
}
