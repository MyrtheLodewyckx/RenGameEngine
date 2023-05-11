#pragma once

namespace dae
{
	class GameObject;
}

class Command
{
public:

	Command(dae::GameObject* go) :player(go){}
	virtual ~Command() = default;

	Command(const Command& other) = delete;
	Command(Command&& other) noexcept = delete;
	Command& operator=(const Command& other) = delete;
	Command& operator=(Command&& other)	noexcept = delete;

	virtual void Execute() {};
	virtual void Execute(float x, float y, const float deltaTime) =0;

	dae::GameObject* player{};
};


