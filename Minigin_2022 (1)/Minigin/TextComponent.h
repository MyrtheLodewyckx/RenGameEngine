#pragma once
#include "Component.h"
#include <string>
#include <memory>

namespace dae
{
	class Font;

	class TextComponent : public Component
	{
	public:
		TextComponent(GameObject* go) : Component(go) {}
		~TextComponent() = default;
		virtual void Update(const float) override;
		virtual void Render() const override;

		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<Font> font);

	private:
		std::shared_ptr<Font> m_Font{};
		std::string m_Text{};
		bool m_NeedsUpdate{true};
	};
}