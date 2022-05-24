#pragma once
#include "TransformComponent.h"
#include "Renderer.h"
#include "Component.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextObject final: public Component
	{
		public:

			virtual void Update(const float) override;
			virtual void Render() const override;

			void SetText(const std::string& text);
			void SetFont();

			explicit TextObject(std::weak_ptr<GameObject> go)
				:Component(go)
			{}
			virtual ~TextObject() override {};
			TextObject(const TextObject& other) = delete;
			TextObject(TextObject&& other) = delete;
			TextObject& operator=(const TextObject& other) = delete;
			TextObject& operator=(TextObject&& other) = delete;


		private:
			bool m_NeedsUpdate;
			std::string m_Text;
			TransformComponent m_TransformComponent;
			Renderer m_RenderComponent;

			std::shared_ptr<Font> m_Font;
			std::shared_ptr<Texture2D> m_TextTexture;
	};
}
