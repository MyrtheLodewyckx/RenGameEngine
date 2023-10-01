#include "SurfaceTexture2D.h"

#include <iostream>
#include <SDL_image.h>

SurfaceTexture2D::SurfaceTexture2D(SDL_Surface* pSurface) :
	m_pSurface{ pSurface },
	m_pSurfacePixels{ (uint32_t*)pSurface->pixels }
{
}

SurfaceTexture2D::~SurfaceTexture2D()
{
	if (m_pSurface)
	{
		SDL_FreeSurface(m_pSurface);
		m_pSurface = nullptr;
	}
}

SDL_Color SurfaceTexture2D::Sample(int x, int y) const
{
    int bpp = m_pSurface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8* p = (Uint8*)m_pSurface->pixels + y * m_pSurface->pitch + x * bpp;
    Uint32 data{};


    switch (bpp)
    {
    case 1:
        data = *p;
        break;

    case 2:
        data = *(Uint16*)p;
        break;

    case 3:
        if constexpr (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            data =  p[0] << 16 | p[1] << 8 | p[2];
        else
            data =  p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        data =  *(Uint32*)p;
        break;

    default:
       data =  0;  
    }


	SDL_Color rgb;
	SDL_GetRGB(data, m_pSurface->format, &rgb.r, &rgb.g, &rgb.b);

    return rgb;
}

glm::vec2 SurfaceTexture2D::GetSize() const
{
	return {m_pSurface->w,m_pSurface->h};
}
