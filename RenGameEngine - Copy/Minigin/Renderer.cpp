#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include  <chrono>
#include "GameObject3D.h"
#include <gl/GL.h>
#include "GameStateManager.h"

std::vector<float> results1{};
std::vector<float> results2{};

int m_AmtOfSteps{11};


int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	GameStateManager::GetInstance().GetCurrent()->Render();
	
	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::Destroy()
{
	/*ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();*/
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}



void dae::Renderer::RenderTexture(const Texture2D& texture, float x, float y, float width, float height, SDL_RendererFlip flip) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, 0, 0, flip);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height, const float sourceX, const float sourceY, const float sourceWidth, const float sourceHeight, SDL_RendererFlip flip) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);

	SDL_Rect srt{};
	srt.x = static_cast<int>(sourceX);
	srt.y = static_cast<int>(sourceY);
	srt.w = static_cast<int>(sourceWidth);
	srt.h = static_cast<int>(sourceHeight);

	//SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &srt, &dst);
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &srt, &dst, 0, 0, flip);
}

