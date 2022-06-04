#pragma once
#include "Component.h"
#include "SpriteComponent.h"
#include "Physics.h"

namespace dae
{
	class Transform;
	class GameObject;

	class PlayerPhysics : public Physics
	{
		static std::vector<PlayerPhysics*> m_ObjectList;

		int m_PlayerIdx{ 0 };

	public:

		int GetPlayerIdx() const { return m_PlayerIdx; };

		static std::vector<PlayerPhysics*> GetAllInstances() { return m_ObjectList; }
		static PlayerPhysics* GetPlayer(int playerIdx);
		virtual MovementDirection GetDirection() override { return m_Direction; }
		virtual void Update(const float) override;
		virtual void Render() const override {};

		void SetControllerIdx(int idx) { m_PlayerIdx = idx; };

		SDL_Rect GetHitBox();
		glm::vec3 GetPos();
		void SetPos(glm::vec3 pos);

		virtual void HandleMovement(const float deltaTime) override;

		PlayerPhysics(GameObject* go);
		~PlayerPhysics();
		PlayerPhysics(const PlayerPhysics& other) = delete;
		PlayerPhysics(PlayerPhysics&& other) = delete;
		PlayerPhysics& operator=(const PlayerPhysics& other) = delete;
		PlayerPhysics& operator=(PlayerPhysics&& other) = delete;
	};
}