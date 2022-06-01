#pragma once
#include "SDL_Render.h"
#include <vector>
#include <glm/detail/type_vec.hpp>
#include "Component.h"


namespace dae
{
	class GameObject;
	class PlayerPhysics;
	class TextureComponent;
	class Ladder: public Component
	{
		static std::vector<Ladder*> m_ObjectList;
		TextureComponent* m_texturePtr = nullptr;
		SDL_Rect m_HitBox{0,0,0,0};

		const void HandlePlayerCollision();
		const void HandleEnemyCollision();

	public:
		virtual void Update(const float) override;
		virtual void Render() const override;
		void SetDimentions(int height, int width);
		Ladder(GameObject* go);
		~Ladder();
	};
}