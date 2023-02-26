#pragma once
#include "Component.h"
#include <string>
#include <memory>
#include "Texture2D.h"


class TextureComponent: public Component
{
	std::shared_ptr<dae::Texture2D> m_texture{};

public: 
	TextureComponent(dae::GameObject* go);
	~TextureComponent();
	void SetTexture(const std::string& filename);
	void SetTexture(std::shared_ptr<dae::Texture2D> texture);

	virtual void Render() const override;
	virtual void Update(const float deltaTime) override;
	virtual void FixedUpdate(const float fixedTimeStep) override;
};