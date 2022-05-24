#include "MiniginPCH.h"
#include "Texture2D.h"

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

float dae::Texture2D::GetWidth()
{
	SDL_Point size{};
	SDL_QueryTexture(m_Texture,NULL,NULL,&size.x,&size.y);

	return (float)size.x;
}

float dae::Texture2D::GetHeight()
{
	SDL_Point size{};
	SDL_QueryTexture(m_Texture, NULL, NULL, &size.x, &size.y);

	return (float)size.y;
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

dae::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}
