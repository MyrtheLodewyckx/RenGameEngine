#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct SDL_Texture;
namespace dae
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D final
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		explicit Texture2D(SDL_Texture* texture);
		~Texture2D();

		glm::ivec2 GetSize() const;

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;

		glm::vec3 Sample(int u, int v) const;
	private:
		SDL_Texture* m_texture;
	};
}
