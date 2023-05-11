#pragma once
#include <SDL_rect.h>
#include <vector>
#include <glm/glm.hpp>

namespace GeoUtils
{
	float cross(glm::vec2 p1, glm::vec2 p2);

	bool IsPointInRect(const glm::vec2& p, const SDL_Rect& r);
	bool IsPointInPolygon(const glm::vec2& p, const std::vector<glm::vec2>& vertices);
	bool IsPointInPolygon(const glm::vec2& p, const glm::vec2* vertices, size_t nrVertices);

	bool IsOverlapping(const glm::vec2& a, const glm::vec2& b, const SDL_Rect& r);
	bool IsOverlapping(const SDL_Rect& r1, const SDL_Rect& r2);
	bool IntersectLineSegments(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& q1, const glm::vec2& q2, float& outLambda1, float& outLambda2, float epsilon = (float)1e-6);
	bool IsPointOnLineSegment(const glm::vec2& p, const glm::vec2& a, const glm::vec2& b);


	struct HitInfo
	{
		float lambda;
		glm::vec2 intersectPoint;
		glm::vec2 normal;
	};

	bool Raycast(const std::vector<glm::vec2>& vertices, const glm::vec2& rayP1, const glm::vec2& rayP2, HitInfo& hitInfo);
	bool Raycast(const glm::vec2* vertices, const size_t nrVertices, const glm::vec2 rayP1, const glm::vec2& rayP2, HitInfo& hitInfo);
}