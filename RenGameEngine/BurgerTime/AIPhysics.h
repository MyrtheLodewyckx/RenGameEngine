#pragma once
#include "Component.h"
#include <vector>
#include "SpriteComponent.h"
#include "GameObject.h"
#include "Physics.h"
#include <SDL_rect.h>
#include <glm/detail/type_vec.hpp>


	class GameObject;
	class Transform;
	class PlayerPhysics;
	class AIPhysics : public Physics
	{
		static std::vector<AIPhysics*> m_ObjectList;

		int m_LadderIdx = -1;
		int m_PlatformIdx = -1;
		float m_Timer = 0.f;

		dae::Transform* m_pTransform = nullptr;
		virtual void HandleMovement(const float deltaTime) override;

	public:
		SDL_Rect GetHitBox();
		virtual void SetPos(glm::vec3 pos) override;
		virtual glm::vec3 GetPos()override { if (!m_pTransform) return glm::vec3(0, 0, 0); else return m_pTransform->GetPosition(); }
		static std::vector<AIPhysics*> GetAllInstances();
		virtual MovementDirection GetDirection() override { return m_Direction; }
		AIPhysics(dae::GameObject* go);
		~AIPhysics();
		virtual void Update(const float deltaTime) override;
		virtual void Render()const override {};
		void SetIsOverLadder(int ladderIndex);
		void SetIsOnPlatform(int platformIndex);
		void SetAiDirection(MovementDirection direction);

	};