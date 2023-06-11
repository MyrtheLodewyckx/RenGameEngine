#pragma once
#include "Component.h"
#include <string>
#include <memory>
#include "Texture2D.h"


class TextureComponent: public Component
{
	std::shared_ptr<dae::Texture2D> m_texture{};
	int m_Width{}, m_Height{};
public: 
	TextureComponent(dae::GameObject* go);
	~TextureComponent() override;
	TextureComponent(const TextureComponent& other) = delete;
	TextureComponent(TextureComponent&& other) noexcept = delete;
	TextureComponent& operator=(const TextureComponent& other) = delete;
	TextureComponent& operator=(TextureComponent&& other)	noexcept = delete;
	void SetTexture(const std::string& filename);
	void SetTexture(std::shared_ptr<dae::Texture2D> texture);
	void SetTexture(const std::string& filename, int width, int height);
	void SetTexture(std::shared_ptr<dae::Texture2D> texture, int width, int height);

	glm::vec2 GetSize();

	virtual void Render() const override;
};