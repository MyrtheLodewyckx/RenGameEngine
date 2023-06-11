#pragma once
#include <memory>

#include "Component.h"
#include <TextComponent.h>

namespace dae
{
	class Renderer;
	class Texture2D;
}

inline int gScore{};


class HUD final: public Component
{
	std::shared_ptr<textComponent> m_pScoreText{};
	int m_Lives{3};
	std::shared_ptr<dae::Texture2D> m_pPacMan_Icon{};
	dae::Renderer* m_pRendererRef{};
public:
	HUD(dae::GameObject* go);
	~HUD() override = default;

	virtual void Update(const float) override;
	virtual void Render() const override;
	void SetScoreTextComp(std::shared_ptr<textComponent> textComponent);
};
