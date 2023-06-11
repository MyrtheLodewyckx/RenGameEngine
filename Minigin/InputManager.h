#pragma once
#include <memory>
#include <vector>

#include "Singleton.h"
#include "PlayerController.h"
#include "Keyboard.h"

class Command;

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
		std::vector<std::unique_ptr<PlayerController>> m_pControllers{};
		std::unique_ptr<Keyboard> m_pKeyBoard{};
	public:
		InputManager();
		bool ProcessInput(const float deltaTime);
		void AddController(std::unique_ptr<PlayerController> controller);
		PlayerController* GetController(int idx) const;
		Keyboard* GetKeyboard() const;
		void ClearControllers();
		void ClearCommands() const;
	};

}
