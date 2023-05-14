#pragma once
#include "Component.h"
#include "Observer.h"

enum class playerEvents
{
	SCORE_CHANGE,
	LIVES_CHANGE
};



class PlayerStatusComponent: public Component, public Observer<playerEvents,int>
{
	int m_Lives{ 3 };
	int m_Score{ 0 };

	virtual void onNotify(playerEvents event, int amt) override;

public:
	PlayerStatusComponent(dae::GameObject* go): Component(go){}
	virtual ~PlayerStatusComponent() override = default;

	void ChangeLives(int amt) { m_Lives += amt; }
	void ChangeScore(int amt) { m_Score += amt; }
	int GetLives() const{ return m_Lives; }
	int GetScore() const{ return m_Score; }
};
