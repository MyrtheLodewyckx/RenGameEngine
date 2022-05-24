#pragma once
#include "Component.h"
#include <string>
#include <memory>


namespace dae
{
	class Texture2D;

	class TextureComponent: public Component
	{

	public:

		TextureComponent(std::weak_ptr<GameObject> go)
			:TextureComponent(go,nullptr)
		{}
		TextureComponent(std::weak_ptr<GameObject> go, std::shared_ptr<Texture2D> texture)
			:Component(go)
			, m_Texture(texture)
		{}
		~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;
		
		virtual void Update(const float) override {};
		virtual void Render() const override {};


		void SetTexture(std::shared_ptr<Texture2D> texture)
		{
			m_Texture = texture;
		}

		std::weak_ptr<Texture2D> GetTexture() { return m_Texture; };

	private:
		std::shared_ptr<Texture2D> m_Texture{};
	};
}
