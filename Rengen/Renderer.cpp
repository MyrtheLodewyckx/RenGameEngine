#include <stdexcept>
#include <cstring>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"


int GetOpenGLDriverIndex()
{
    int openglIndex = -1;
    const int driverCount = SDL_GetNumRenderDrivers();
    for (int i = 0; i < driverCount; ++i)
    {
        SDL_RendererInfo info{};
        if (SDL_GetRenderDriverInfo(i, &info) == 0)
        {
            if (std::strcmp(info.name, "opengl") == 0)
            {
                openglIndex = i;
                break; // stop at first match
            }
        }
    }
    return openglIndex;
}

SDL_Window* dae::Renderer::get_window()
{
    return m_window;
}

void dae::Renderer::Init(SDL_Window* window)
{
    m_window = window;

    const Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    m_renderer = SDL_CreateRenderer(window, -1, flags);

    if (!m_renderer)
        throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());

    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
}

void dae::Renderer::Render() const
{
    const auto& color = GetBackgroundColor();
    SDL_SetRenderDrawColor(m_renderer,
        static_cast<Uint8>(color.r),
        static_cast<Uint8>(color.g),
        static_cast<Uint8>(color.b),
        static_cast<Uint8>(color.a));
    SDL_RenderClear(m_renderer);

    SceneManager::GetInstance().Render();
    SceneManager::GetInstance().PostRender();

    SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
}

void dae::Renderer::RenderTexture(const Texture2D& texture, float x, float y) const
{
    SDL_Rect dst{};
    dst.x = static_cast<int>(x);
    dst.y = static_cast<int>(y);

    SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);

    SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture,
    float x, float y, float width, float height,
    SDL_RendererFlip flip) const
{
    SDL_Rect dst{
        static_cast<int>(x), static_cast<int>(y),
        static_cast<int>(width), static_cast<int>(height)
    };
    SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, 0.0, nullptr, flip);
}

void dae::Renderer::RenderTexture(const Texture2D& texture,
    float x, float y, float width, float height,
    float sourceX, float sourceY, float sourceWidth, float sourceHeight,
    SDL_RendererFlip flip) const
{
    SDL_Rect dst{
        static_cast<int>(x), static_cast<int>(y),
        static_cast<int>(width), static_cast<int>(height)
    };

    SDL_Rect src{
        static_cast<int>(sourceX), static_cast<int>(sourceY),
        static_cast<int>(sourceWidth), static_cast<int>(sourceHeight)
    };

    SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst, 0.0, nullptr, flip);
}

inline SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }
