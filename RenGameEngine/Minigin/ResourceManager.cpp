#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"
#include <gl/GL.h>

void dae::ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<dae::Texture2D> dae::ResourceManager::LoadTexture(const std::string& file) const
{
	const auto fullPath = m_DataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_shared<Texture2D>(texture);
}

std::shared_ptr<dae::Font> dae::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return std::make_shared<Font>(m_DataPath + file, size);
}

std::shared_ptr<dae::Texture2D> dae::ResourceManager::LoadTextureFromFont(std::shared_ptr<Font> font, std::string text, SDL_Colour color) const
{
	SDL_Surface* pLoadedSurface = TTF_RenderText_Blended(font.get()->GetFont(), text.c_str(), color);
	if (pLoadedSurface == nullptr)
	{
		std::cerr << "Texture::CreateFromString, error when calling TTF_RenderText_Blended: " << TTF_GetError() << std::endl;
		return nullptr;
	}

	// Get pixel format information and translate to OpenGl format
	GLenum pixelFormat{ GL_RGB };
	switch (pLoadedSurface->format->BytesPerPixel)
	{
	case 3:
		if (pLoadedSurface->format->Rmask == 0x000000ff)
		{
			pixelFormat = GL_RGB;
		}
		else
		{
			pixelFormat = GL_BGR_EXT;
		}
		break;
	case 4:
		if (pLoadedSurface->format->Rmask == 0x000000ff)
		{
			pixelFormat = GL_RGBA;
		}
		else
		{
			pixelFormat = GL_BGRA_EXT;
		}
		break;
	default:
		std::cerr << "Texture::CreateFromSurface, unknow pixel format, BytesPerPixel: " << pLoadedSurface->format->BytesPerPixel << "\nUse 32 bit or 24 bit images.\n";
		return nullptr;
	}

	GLuint TextureId{};

	glGenTextures(1, &TextureId);
	glBindTexture(GL_TEXTURE_2D, TextureId);
	GLenum e = glGetError();
	if (e != GL_NO_ERROR)
		std::cerr << "Texture::CreateFromSurface, error binding textures, Error id = " << e << '\n';

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pLoadedSurface->w, pLoadedSurface->h, 0, pixelFormat, GL_UNSIGNED_BYTE, pLoadedSurface->pixels);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	auto t = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), pLoadedSurface);

	return std::make_shared<Texture2D>(t);
}
