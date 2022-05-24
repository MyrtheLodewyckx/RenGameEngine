#pragma once
#include "Component.h"
#include <vector>
#include "SpriteComponent.h"

namespace dae
{
	enum class EnemyID
	{
		MrHotDog,
		MrEgg,
		MrPickle
	};

	enum class EnemyDirection
	{
		Up,
		Down,
		Left,
		Right
	};

	class GameObject;
	class Transform;
	class PlayerPhysics;
	class Enemy : public dae::Component
	{
		static std::vector<Enemy*> m_ObjectList;

		//SPRITES
		std::shared_ptr<Texture2D> m_pWalkingTexture{ nullptr };
		std::shared_ptr<Texture2D> m_pClimbingDownTexture{ nullptr };
		std::shared_ptr<Texture2D> m_pClimbingUpTexture{ nullptr };
		dae::Sprite m_Sprites[3]
		{
			{m_pClimbingDownTexture,1,2,0.25f},
			{m_pWalkingTexture,1,2,0.25f},
			{m_pClimbingUpTexture,1,2,0.25f}
		};

		int m_Width = 0;
		int m_Height = 0;

		EnemyDirection m_Direction;

		int m_LadderIdx = -1;
		int m_PlatformIdx = -1;

		Transform* m_pTransform = nullptr;
		SpriteComponent* m_pSprite = nullptr;
		void HandleMovement(const float deltaTime);
		void HandlePlayerCollision();

	public:

		SDL_Rect GetHitBox();
		void SetPos(glm::vec3 pos);
		static std::vector<Enemy*> GetAllInstances();
		void SetValues(EnemyID id, int height, int width);
		Enemy(GameObject* go);
		virtual void Update(const float deltaTime) override;
		virtual void Render()const override {};
		void SetIsOverLadder(int ladderIndex);
		void SetIsOnPlatform(int platformIndex);
		void SetEnemyDirection(EnemyDirection direction);

	};
}