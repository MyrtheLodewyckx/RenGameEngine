#pragma once
#include <memory>
#include <vector>

#include "Singleton.h"
#include "PlayerController.h"



class PlayerController;
class Command;

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
		std::vector<std::shared_ptr<PlayerController>> m_pControllers{};

	public:
		bool ProcessInput(const float deltaTime);
		void AddController(std::shared_ptr<PlayerController> controller);
	};

}
