#pragma once
#include "Component.h"


class Texture2D;

namespace dae
{
	class TextureRenderComponent : public Component
	{
	public:
		TextureRenderComponent(std::weak_ptr<GameObject> go)
			:Component(go)
		{}
		~TextureRenderComponent() = default;

		virtual void Update(const float) override {};
		virtual void Render() const override;
		void SetTexture(std::weak_ptr<Texture2D> texture)
		{
			m_TexturePtr = texture;
		}

	private:
		std::weak_ptr<Texture2D> m_TexturePtr;
	};
}