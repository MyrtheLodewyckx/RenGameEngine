#include "Options.h"

#include "PacManInstance.h"
#include "ResourceManager.h"


void OptionsNavigate::Execute(float x, float , const float )
{
	if (!m_CanRecieveInput)
		return;

	m_CanRecieveInput = false;
	const int amtModes{ 3 };

	int currentMode = (int)PacManInstance::GetMode();

	if (x > 0)
	{
		PacManInstance::SetMode(mode(unsigned(currentMode+1)%amtModes));
	}
	else if (x < 0)
		PacManInstance::SetMode(mode(unsigned(currentMode - 1) % amtModes));
}


Options::Options():Scene("Options")
{
}

void Options::Initialize()
{
	SDL_GetWindowSize(dae::Renderer::GetInstance().get_window(), &m_WindowWidth, &m_WindowHeight);

	auto& resourceRf = dae::ResourceManager::GetInstance();
	m_pFont = resourceRf.LoadFont("Fonts/pixel.otf", 40);

	m_pArrowButtonTexture = resourceRf.LoadTexture("Arrow.png");

	m_pGameModeObject = std::make_shared<dae::GameObject>();
	m_pGameModeTexture = m_pGameModeObject->AddComponent<TextureComponent>();
	m_pGameModeText = m_pGameModeObject->AddComponent<textComponent>();
	m_pGameModeText->SetText("SINGLE PLAYER");
	m_pGameModeText->SetFont(m_pFont);
	m_pGameModeText->SetColor(SDL_Color{ 255,255,255,255 });


	m_pNavigateCommand = std::make_unique<OptionsNavigate>(nullptr);
	m_pNavigateLeftCommand = std::make_unique<OptionsNavigateLeft>(nullptr);
	m_pNavigateRightCommand = std::make_unique<OptionsNavigateRight>(nullptr);
	m_pReturnCommand = std::make_unique<OptionsReturn>(nullptr);

	auto pInput = &dae::InputManager::GetInstance();
	pInput->GetKeyboard()->AddCommand(SDL_SCANCODE_A, KeyState::IsPressed, m_pNavigateLeftCommand.get());
	pInput->GetKeyboard()->AddCommand(SDL_SCANCODE_D, KeyState::IsPressed, m_pNavigateRightCommand.get());
	pInput->GetKeyboard()->AddCommand(SDL_SCANCODE_RETURN, KeyState::IsPressed, m_pReturnCommand.get());

	pInput->GetController(0)->AddCommand(ControllerButton::LEFT_THUMB, KeyState::none, m_pNavigateCommand.get());
	pInput->GetController(0)->AddCommand(ControllerButton::ButtonA, KeyState::IsPressed, m_pReturnCommand.get());

	Add(m_pGameModeObject);
}


void Options::Update(const float deltaTime)
{

	if (!m_pNavigateCommand->m_CanRecieveInput)
	{
		m_CurrentTime += deltaTime;
		if (m_CurrentTime >= m_Delay)
		{
			m_CurrentTime = 0;
			m_pNavigateCommand->m_CanRecieveInput = true;
		}
	}

	glm::vec3 pos{};

	switch (PacManInstance::GetMode())
	{
	case mode::singlePlayer:
		m_pGameModeText->SetText("SINGLE PLAYER");
		break;
	case mode::co_up:
		m_pGameModeText->SetText("CO-UP");
		break;
	case mode::versus:
		m_pGameModeText->SetText("VERSUS");
		break;
	}

	m_pGameModeText->Update(deltaTime);

	pos.x = m_WindowWidth*0.5f - m_pGameModeTexture->GetSize().x * 0.5f;
	pos.y = m_WindowHeight*0.5f - m_pGameModeTexture->GetSize().y * 0.5f;

	m_pGameModeObject->SetPosition(pos);
}


void OptionsReturn::Execute()
{
	dae::SceneManager::GetInstance().PopCurrent();
}

void OptionsNavigateLeft::Execute()
{
	int currentMode = (int)PacManInstance::GetMode();

	const int amtModes{ 3 };
	PacManInstance::SetMode(mode(unsigned(currentMode - 1) % amtModes));
}

void OptionsNavigateRight::Execute()
{
	int currentMode = (int)PacManInstance::GetMode();

	const int amtModes{ 3 };
	PacManInstance::SetMode(mode(unsigned(currentMode + 1) % amtModes));
}
