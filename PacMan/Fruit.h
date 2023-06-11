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
	Fruit(const Fruit& other) = delete;
	Fruit(Fruit&& other) noexcept = delete;
	Fruit& operator=(const Fruit& other) = delete;
	Fruit& operator=(Fruit&& other)	noexcept = delete;
	virtual void Initialize() override;
	virtual void Update(float delta) override;
	static bool GetIsAlive();

};
