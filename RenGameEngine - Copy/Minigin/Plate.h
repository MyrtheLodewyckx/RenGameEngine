#pragma once
#include "Component.h"
#include <SDL_ttf.h>
#include <vector>


namespace dae
{
	class GameObject;
	class TextureComponent;
	class Plate : public Component
	{
		static std::vector<Plate*> m_ObjectList;
		SDL_Rect m_HitBox{ 0,0,0,0 };
		TextureComponent* m_pTexture = nullptr;

	public:
		static std::vector<Plate*> GetAllInstances() { return m_ObjectList; }
		virtual void Update(const float) override;
		virtual void Render()const override;
		void SetDimentions(int width, int height);
		SDL_Rect GetDimentions() { return m_HitBox; }
		Plate(GameObject* go);
	};
}