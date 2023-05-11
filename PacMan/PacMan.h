#pragma once
#include <memory>
#include <vector>

#include "Component.h"


namespace dae
{
	class SpriteComponent;
}

class PacMan: public Component
{
	std::shared_ptr<dae::SpriteComponent> m_Sprite{nullptr};
	std::vector<std::shared_ptr<dae::GameObject>> m_PelletsRef{};
	void CheckForPellets();

public:
	PacMan(dae::GameObject* go):Component(go){}

	void SetDimentions(int width, int height);

	void Update(const float) override;
	void Initialize() override;
};
