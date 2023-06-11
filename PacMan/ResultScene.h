#pragma once
#include "Scene.h"

class Results : public dae::Scene
{

public:
	Results();
	~Results() override = default;

	void Initialize() override;
};
