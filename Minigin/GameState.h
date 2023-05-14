#pragma once

namespace dae
{
	class GameState
	{
	public:
		GameState() {}
		virtual ~GameState() {}

		virtual void Initialize() = 0;
		virtual void HandleInput() = 0;
		virtual void Render() const = 0;
		virtual void Update(const float deltaTime) = 0;

		virtual void Pause() {}
		virtual void Start() {}
	};
}