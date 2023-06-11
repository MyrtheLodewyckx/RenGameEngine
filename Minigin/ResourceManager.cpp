#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"

#include <iostream>
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"
#include "SurfaceTexture2D.h"

void dae::ResourceManager::Init(const std::string& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<dae::Texture2D> dae::ResourceManager::LoadTexture(const std::string& file) const
{
	const auto fullPath = m_dataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_shared<Texture2D>(texture);
}

std::shared_ptr<SurfaceTexture2D> dae::ResourceManager::LoadSurface(const std::string& file) const
{
	const auto fullPath = m_dataPath + file;

	auto surface = IMG_Load(fullPath.c_str());

	if (surface == nullptr)
	{
		std::cout << "Could not load SurfaceTexture2D from file.";
		return {};
	}

	return std::make_shared<SurfaceTexture2D>(IMG_Load(fullPath.c_str()));
}

std::shared_ptr<dae::Font> dae::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return std::make_shared<Font>(m_dataPath + file, size);
}

std::shared_ptr<dae::Texture2D> dae::ResourceManager::LoadTextureFromFont(std::shared_ptr<Font> font, std::string text, SDL_Colour color) const
{

	SDL_Surface* pLoadedSurface = TTF_RenderText_Blended(font.get()->GetFont(), text.c_str(), color);
	if (pLoadedSurface == nullptr)
	{
		std::cerr << "Texture::CreateFromString, error when calling TTF_RenderText_Blended: " << TTF_GetError() << std::endl;
		return nullptr;
	}

	auto t = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), pLoadedSurface);

	if (t == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(pLoadedSurface);

	return std::make_shared<Texture2D>(t);
}