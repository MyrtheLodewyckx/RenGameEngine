#include "MiniginPCH.h"
#include "Options.h"
#include "ResourceManager.h"



void Options::ControllerUpdate()
{
	if (m_InputManagerRef.IsPressed(dae::ControllerButton::ButtonB, 0))
		dae::GameStateManager::GetInstance().PopCurrent();
	else if (m_InputManagerRef.IsPressed(dae::ControllerButton::ButtonA, 0))
	{
		switch (m_lvls)
		{
		case 1:
			m_InputManagerRef.ChangePlayerInputDevice(0, dae::InputDevices(m_Player1SelectedInputDevice));
			break;
		case 2:
			m_InputManagerRef.ChangePlayerInputDevice(1, dae::InputDevices(m_Player2SelectedInputDevice));
			break;
		}
	}
}

void Options::KeyboardUpdate()
{
	if (m_InputManagerRef.IsPressed(SDL_SCANCODE_BACKSPACE))
		dae::GameStateManager::GetInstance().PopCurrent();
	else if (m_InputManagerRef.IsPressed(SDL_SCANCODE_RETURN))
	{
		switch (m_lvls)
		{
		case 1:
			m_InputManagerRef.ChangePlayerInputDevice(0, dae::InputDevices(m_Player1SelectedInputDevice));
			break;
		case 2:
			m_InputManagerRef.ChangePlayerInputDevice(1, dae::InputDevices(m_Player2SelectedInputDevice));
			break;
		}
	}
}

Options::Options()
{
}

Options::~Options()
{
}

void Options::Init()
{
	auto& resourceRf = dae::ResourceManager::GetInstance();
	m_Font = resourceRf.LoadFont("pixel.otf", 20);

	m_GameModeTexture.emplace_back(resourceRf.LoadTextureFromFont(m_Font, "SINGLE PLAYER"));
	m_GameModeTexture.emplace_back(resourceRf.LoadTextureFromFont(m_Font, "CO-UP"));
	m_GameModeTexture.emplace_back(resourceRf.LoadTextureFromFont(m_Font, "VERSUS"));


	m_pArrowButtonTexture = resourceRf.LoadTexture("Arrow.png");
	m_InputDevicesTexture.emplace_back(resourceRf.LoadTexture("Keyboard.png"));
	m_InputDevicesTexture.emplace_back(resourceRf.LoadTexture("Controller.png"));
	m_pPeterHeadIcon = resourceRf.LoadTexture("PeterHead.png");


	m_pPlayer1 = resourceRf.LoadTextureFromFont(m_Font, "PLAYER 1");
	m_pPlayer2 = resourceRf.LoadTextureFromFont(m_Font, "PLAYER 2");

	m_GameModeTexture.shrink_to_fit();
}

void Options::HandleInput()
{
	auto j = m_InputManagerRef.GetMenuDirection(0);

	int maxLvls = 3;
	if (m_GameModeRef == dae::GameMode::SinglePlayer)
		maxLvls = 2;

	//SCROLL TROUGH LEVELS
	if (j == dae::Direction::Up)
	{
		m_lvls = unsigned int(m_lvls - 1) % maxLvls;
	}
	else if (j == dae::Direction::Down)
		m_lvls = unsigned int(m_lvls + 1) % maxLvls;

	//SCROLL THROUGH OPTIONS
	else if(j == dae::Direction::Left)
	{
		switch (m_lvls)
		{
		case 0:
		{
			dae::GameMode lastGameMode = m_GameModeRef;
			m_GameModeRef = dae::GameMode(((unsigned int)m_GameModeRef - 1) % m_GameModeTexture.size());
			if (m_GameModeRef == dae::GameMode::SinglePlayer)
				m_InputManagerRef.RemovePlayer();
			else if ((m_GameModeRef == dae::GameMode::CoUp || m_GameModeRef == dae::GameMode::Versus) && lastGameMode == dae::GameMode::SinglePlayer)
				m_InputManagerRef.AddPlayer(dae::InputDevices(m_Player2SelectedInputDevice));
		}
			break;
		case 1:
			m_Player1SelectedInputDevice = unsigned int(m_Player1SelectedInputDevice - 1) % m_InputDevicesTexture.size();
			break;
		case 2:
			m_Player2SelectedInputDevice = unsigned int(m_Player2SelectedInputDevice - 1) % m_InputDevicesTexture.size();
			break;
		}
	}
	else if(j == dae::Direction::Right)
	{
		switch (m_lvls)
		{
		case 0:
		{
			dae::GameMode lastGameMode = m_GameModeRef;
			m_GameModeRef = dae::GameMode(((unsigned int)m_GameModeRef + 1) % m_GameModeTexture.size());
			if (m_GameModeRef == dae::GameMode::SinglePlayer)
				m_InputManagerRef.RemovePlayer();
			else if ((m_GameModeRef == dae::GameMode::CoUp || m_GameModeRef == dae::GameMode::Versus) && lastGameMode == dae::GameMode::SinglePlayer)
				m_InputManagerRef.AddPlayer(dae::InputDevices(m_Player2SelectedInputDevice));
		}
			break;
		case 1:
			m_Player1SelectedInputDevice = unsigned int(m_Player1SelectedInputDevice + 1) % m_InputDevicesTexture.size();
			break;
		case 2:
			m_Player2SelectedInputDevice = unsigned int(m_Player2SelectedInputDevice + 1) % m_InputDevicesTexture.size();
			break;
		}
	}
	auto inDevice = m_InputManagerRef.GetInputDevice(0);

	if (inDevice == dae::InputDevices::KeyBoard)
		KeyboardUpdate();
	else if (inDevice == dae::InputDevices::XBoxController)
		ControllerUpdate();
}

void Options::Update(const float)
{
	
}

void Options::Render() const
{
	int spacer = 10;
	int windowWidth{ 0 };
	int windowHeight{ 0 };
	SDL_GetWindowSize(m_RendererRef.GetWindow(), &windowWidth, &windowHeight);

	glm::vec2 gameModePos{ windowWidth/2 - m_GameModeTexture[(int)m_GameModeRef]->GetWidth() / 2, windowHeight/4 - m_GameModeTexture[(int)m_GameModeRef]->GetHeight() / 2 };
	m_RendererRef.RenderTexture(*m_GameModeTexture[(int)m_GameModeRef].get(), gameModePos.x, gameModePos.y);

	m_RendererRef.RenderTexture(*m_pArrowButtonTexture.get(), gameModePos.x - spacer - m_GameModeTexture[(int)m_GameModeRef]->GetHeight(), gameModePos.y, m_GameModeTexture[(int)m_GameModeRef]->GetHeight(), m_GameModeTexture[(int)m_GameModeRef]->GetHeight(),SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
	m_RendererRef.RenderTexture(*m_pArrowButtonTexture.get(), gameModePos.x + spacer + m_GameModeTexture[(int)m_GameModeRef]->GetWidth(), gameModePos.y, m_GameModeTexture[(int)m_GameModeRef]->GetHeight(), m_GameModeTexture[(int)m_GameModeRef]->GetHeight());


	const int InputIconWidth = 100;
	const int InputIconHeight = 60;

	glm::vec2 player1InputPos{ windowWidth / 2 - InputIconWidth / 2,windowHeight / 4 * 2 };

	m_RendererRef.RenderTexture(*m_InputDevicesTexture[m_Player1SelectedInputDevice].get(), player1InputPos.x, player1InputPos.y, InputIconWidth, InputIconHeight);

	m_RendererRef.RenderTexture(*m_pArrowButtonTexture.get(), player1InputPos.x - spacer - m_GameModeTexture[(int)m_GameModeRef]->GetHeight(), player1InputPos.y, m_GameModeTexture[(int)m_GameModeRef]->GetHeight(), m_GameModeTexture[(int)m_GameModeRef]->GetHeight(), SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
	m_RendererRef.RenderTexture(*m_pArrowButtonTexture.get(), player1InputPos.x + InputIconWidth + spacer, player1InputPos.y, m_GameModeTexture[(int)m_GameModeRef]->GetHeight(), m_GameModeTexture[(int)m_GameModeRef]->GetHeight());

	player1InputPos.y = player1InputPos.y - spacer - m_pPlayer1->GetHeight();
	m_RendererRef.RenderTexture(*m_pPlayer1.get(), player1InputPos.x + InputIconWidth / 2 - m_pPlayer1->GetWidth() / 2, player1InputPos.y);


	glm::vec2 player2InputPos{ player1InputPos.x ,windowHeight / 4 * 3 };

	if (m_GameModeRef == dae::GameMode::CoUp || m_GameModeRef == dae::GameMode::Versus)
	{
		m_RendererRef.RenderTexture(*m_InputDevicesTexture[m_Player2SelectedInputDevice].get(), player2InputPos.x, player2InputPos.y, InputIconWidth, InputIconHeight);

		m_RendererRef.RenderTexture(*m_pArrowButtonTexture.get(), player2InputPos.x - spacer - m_GameModeTexture[(int)m_GameModeRef]->GetHeight(), player2InputPos.y, m_GameModeTexture[(int)m_GameModeRef]->GetHeight(), m_GameModeTexture[(int)m_GameModeRef]->GetHeight(), SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
		m_RendererRef.RenderTexture(*m_pArrowButtonTexture.get(), player2InputPos.x + InputIconWidth + spacer, player2InputPos.y, m_GameModeTexture[(int)m_GameModeRef]->GetHeight(), m_GameModeTexture[(int)m_GameModeRef]->GetHeight());

		player2InputPos.y = player2InputPos.y - spacer - m_pPlayer1->GetHeight();
		m_RendererRef.RenderTexture(*m_pPlayer2.get(), player2InputPos.x + InputIconWidth / 2 - m_pPlayer1->GetWidth() / 2, player2InputPos.y);
	}

	//RENDER SELECTION ICON
	glm::vec2 headIconPos{ windowWidth / 2,0 };
	int iconSizeMultiplier{ 2 };

	switch (m_lvls)
	{
	case 0:
		headIconPos.y = gameModePos.y - spacer - m_pPeterHeadIcon->GetHeight()*iconSizeMultiplier;
		break;
	case 1:
		headIconPos.y = player1InputPos.y - spacer - m_pPeterHeadIcon->GetHeight()*iconSizeMultiplier;
		break;
	case 2:
		headIconPos.y = player2InputPos.y - spacer - m_pPeterHeadIcon->GetHeight()*iconSizeMultiplier;
		break;
	}

	m_RendererRef.RenderTexture(*m_pPeterHeadIcon.get(), headIconPos.x, headIconPos.y, m_pPeterHeadIcon->GetHeight() * iconSizeMultiplier, m_pPeterHeadIcon->GetHeight() * iconSizeMultiplier);

}
