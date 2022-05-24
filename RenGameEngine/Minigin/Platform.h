#pragma once
#include "Component.h"
#include <SDL_ttf.h>


namespace dae
{
	class GameObject;
	class TextureComponent;
	class Platform : public Component
	{
		static std::vector<Platform*> m_ObjectList;
		SDL_Rect m_HitBox{0,0,0,0};
		TextureComponent* m_texturePtr = nullptr;
		void HandlePlayerCollision();
		void HandleEnemyCollision();

	public:
		static std::vector<Platform*> GetAllInstances() { return m_ObjectList; }
		virtual void Update(const float deltaTime) override;
		virtual void Render()const override;
		void SetDimentions(int width, int height);
		SDL_Rect GetDimentions() { return m_HitBox; }
		Platform(GameObject* go);
	};
}