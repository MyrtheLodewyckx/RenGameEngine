#pragma once
#include <Windows.h>
#include "xinput.h"
#include <map>
#include "Command.h"
#include "Singleton.h"


namespace dae
{


	enum class ControllerButton
	{
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,
	};

	class Input final : public Singleton<Input>
	{
		Jump* m_JumpCommand = new Jump{};
		Sing* m_SingCommand = new Sing{};
		Dance* m_DanceCommand = new Dance{};
		Die* m_DieCommand = new Die{};

		std::map<ControllerButton, Command*> m_ConsoleCommand
		{
			{ControllerButton::ButtonB,m_JumpCommand},
			{ControllerButton::ButtonA, m_SingCommand},
			{ControllerButton::ButtonY,m_DanceCommand},
			{ControllerButton::ButtonX, m_DieCommand}
		};

	public:
		Command* GetCommand(ControllerButton Button)
		{
			return m_ConsoleCommand.find(Button)->second;
		}

		~Input()
		{
			delete m_DanceCommand;
			m_DanceCommand = nullptr;
			delete m_SingCommand;
			m_SingCommand = nullptr;
			delete m_DieCommand;
			m_DieCommand = nullptr;
			delete m_JumpCommand;
			m_JumpCommand = nullptr;
		}
	};
}