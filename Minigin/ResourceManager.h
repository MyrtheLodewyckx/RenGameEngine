#pragma once
#include <string>
#include <memory>
#include "Singleton.h"
#include <SDL_ttf.h>

class SurfaceTexture2D;

namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;
		std::shared_ptr<SurfaceTexture2D> LoadSurface(const std::string& file) const;
		std::shared_ptr<dae::Font> LoadFont(const std::string& file, unsigned int size) const;
		std::shared_ptr<Texture2D> LoadTextureFromFont(std::shared_ptr<Font> font, std::string text, SDL_Colour color = SDL_Colour(255, 255, 255)) const;

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_dataPath;
	};
}
