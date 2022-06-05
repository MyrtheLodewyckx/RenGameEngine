#pragma once
#include "Component.h"


namespace dae
{
	class Transform;
	class Movement
	{
	public:
		Movement() = default;
		void MoveHorizontally(const float deltaTime, const int speed, Transform* transform);
		void MoveVertically(const float deltaTime, const int speed, Transform* transform);
	};
}