#pragma once
#include <memory>
#include "Component.h"



namespace dae
{
	class GameObject;
	class Texture2D;

	class TextureComponent: public Component
	{
		
		std::shared_ptr<Texture2D> m_TexturePtr{ nullptr };

	public:
		TextureComponent(GameObject* go) :Component(go) {}
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&&other) = delete;
		virtual void Update(const float) override {};
		virtual void Render() const override;
		void SetTexture(std::shared_ptr<Texture2D> texture) { m_TexturePtr = texture; };
		std::shared_ptr<Texture2D> GetTexture() { return m_TexturePtr; };
	};
}