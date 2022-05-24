#pragma once
#include <SDL_ttf.h>
#include <glm/detail/type_vec.hpp>


class Collision
{
public:
	static bool IsOverlapping(SDL_Rect r1, SDL_Rect r2);
	static bool IsInRect(SDL_Rect rect, glm::vec2 pos);
};