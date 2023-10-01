#pragma once
#include <string>
#include <SDL_ttf.h>
#include "Component.h"
#include <memory>


namespace dae
{
	class Font;
}

class textComponent: public Component
{
	std::shared_ptr<dae::Font> m_font;
	std::string m_text{"input text"};
	SDL_Color m_Color{ 255,255,255 };
	bool m_needsUpdate{ true };

public:
	textComponent(dae::GameObject* go);
	~textComponent();
	textComponent(const textComponent& other) = delete;
	textComponent(textComponent&& other) noexcept = delete;
	textComponent& operator=(const textComponent& other) = delete;
	textComponent& operator=(textComponent&& other)	noexcept = delete;

	void SetFont(std::shared_ptr<dae::Font> font);
	void SetText(const std::string& text);
	void SetColor(SDL_Color color);

	virtual void Update(const float deltaTime) override;
};