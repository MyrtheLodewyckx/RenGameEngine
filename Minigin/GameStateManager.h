#pragma once
#include "Singleton.h"
#include <stack>
#include <memory>
#include "GameState.h"
#include "GameObject.h"

namespace dae
{
	class Scene;

	class GameStateManager final : public Singleton<GameStateManager>
	{
	private:
		std::stack<std::unique_ptr<GameState>> m_StateStack;
		std::unique_ptr<GameState> m_newState;
		bool m_IsPaused = false;
		friend class Singleton<GameStateManager>;

		bool m_add = false;
		bool m_replace = false;
		bool m_remove = false;


	public:
		GameStateManager() = default;
		virtual ~GameStateManager() override = default;
		void Add(std::unique_ptr<GameState> toAdd, bool replace = false);
		void PopCurrent();
		void ProcessStateChange();
		std::unique_ptr<GameState>& GetCurrent();
	};
}
