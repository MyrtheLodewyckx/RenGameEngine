#pragma once
#include <vector>

#include "Component.h"
#include <TextureComponent.h>



class Fruit: public Component
{
	std::vector<dae::GameObject*> m_pPacmanRef{};
	int m_CurrentLevel{1};
	std::shared_ptr<TextureComponent> m_pTexture{};
	int m_PacSize{};
	inline static bool m_IsAlive{};
public:
	Fruit(dae::GameObject* go): Component(go){}
	~Fruit() override;
	virtual void Initialize() override;
	virtual void Update(float delta) override;
	static bool GetIsAlive();

};
