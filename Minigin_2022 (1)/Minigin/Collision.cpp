#include "MiniginPCH.h"
#include "Collision.h"

bool Collision::IsOverlapping(SDL_Rect r1, SDL_Rect r2)
{
	if (((r1.x >= r2.x && r1.x <= r2.x + r2.w) || (r2.x >= r1.x && r2.x <= r1.x + r1.w))
		&& ((r1.y >= r2.y && r1.y <= r2.y + r2.h) || (r2.y >= r1.y && r2.y <= r1.y + r1.h)))
		return true;
	else return false;
}

bool Collision::IsInRect(SDL_Rect rect, glm::vec2 pos)
{
	if (pos.x >= rect.x && pos.x <= rect.x + rect.w
		&& pos.y >= rect.y && pos.y <= rect.y + rect.h)
		return true;
	else return false;
}
