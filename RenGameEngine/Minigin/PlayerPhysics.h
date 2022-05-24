#pragma once
#include "Component.h"
#include "SpriteComponent.h"

namespace dae
{
	class Transform;
	class GameObject;

	class PlayerPhysics : public Component
	{
		static std::vector<PlayerPhysics*> m_ObjectList;

		int m_ControllerIdx{ 0 };
		Transform* m_TransformPtr = nullptr;
		SpriteComponent* m_Sprite = nullptr;
		float m_Height, m_Width = 0;

		//SPRITES
		std::shared_ptr<Texture2D> m_pWalkingTexture{ nullptr };
		std::shared_ptr<Texture2D> m_pClimbingDownTexture{ nullptr };
		std::shared_ptr<Texture2D> m_pClimbingUpTexture{ nullptr };
		dae::Sprite m_Sprites[3]
		{
			{m_pClimbingDownTexture,1,3,0.5f},
			{m_pWalkingTexture,1,3,0.5f},
			{m_pClimbingUpTexture,1,3,0.5f}
		};

	public:

		bool m_IsOnLadder = false;
		bool m_IsOnGround = true;
		int GetControllerIdx() const { return m_ControllerIdx; };

		static std::vector<PlayerPhysics*> GetAllInstances() { return m_ObjectList; }

		virtual void Update(const float) override;
		virtual void Render() const override {};

		void SetDimentions(float height, float width);
		void SetControllerIdx(int idx) { m_ControllerIdx = idx; };

		SDL_Rect GetHitBox();
		glm::vec3 GetPos() const;
		void SetPos(glm::vec3 pos);

		void HandlePhysics(const float deltaTime);

		PlayerPhysics(GameObject* go);
		~PlayerPhysics() = default;
		PlayerPhysics(const PlayerPhysics& other) = delete;
		PlayerPhysics(PlayerPhysics&& other) = delete;
		PlayerPhysics& operator=(const PlayerPhysics& other) = delete;
		PlayerPhysics& operator=(PlayerPhysics&& other) = delete;
	};
}