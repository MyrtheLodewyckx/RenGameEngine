#pragma once
#include "Scene.h"

class Results : public dae::Scene
{

public:
	Results();
	~Results() override = default;
	Results(const Results& other) = delete;
	Results(Results&& other) noexcept = delete;
	Results& operator=(const Results& other) = delete;
	Results& operator=(Results&& other)	noexcept = delete;

	void Initialize() override;
};
