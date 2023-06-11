#pragma once
#include <memory>
#include <SDL_surface.h>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class SurfaceTexture2D
{
public:
	SurfaceTexture2D(SDL_Surface* pSurface);
	~SurfaceTexture2D();

	SDL_Color Sample(int x, int y) const;
	glm::vec2 GetSize() const;

	//static SurfaceTexture2D* LoadFromFile(const std::string& path);

private:

	SDL_Surface* m_pSurface{ nullptr }; 
	uint32_t* m_pSurfacePixels{ nullptr };
};

