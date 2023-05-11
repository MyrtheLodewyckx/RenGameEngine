#include "GeometryUtils.h"

#include <algorithm>

float GeoUtils::cross(glm::vec2 p1, glm::vec2 p2)
{
	return p1.x * p2.y - p1.y * p2.x;
}

bool GeoUtils::IsPointInRect(const glm::vec2& p, const SDL_Rect& r)
{
	return ((int)p.x >= r.x &&
		(int)p.x <= r.x + r.w &&
		(int)p.y >= r.y &&
		(int)p.y <= r.y + r.h);
}

bool GeoUtils::IsPointInPolygon(const glm::vec2& p, const std::vector<glm::vec2>& vertices)
{
	return IsPointInPolygon(p, vertices.data(), vertices.size());
}

bool GeoUtils::IsPointInPolygon(const glm::vec2& p, const glm::vec2* vertices, size_t nrVertices)
{
	if (nrVertices < 2)
	{
		return false;
	}
	// 1. First do a simple test with axis aligned bounding box around the polygon
	float xMin{ vertices[0].x };
	float xMax{ vertices[0].x };
	float yMin{ vertices[0].y };
	float yMax{ vertices[0].y };
	for (size_t idx{ 1 }; idx < nrVertices; ++idx)
	{
		if (xMin > vertices[idx].x)
		{
			xMin = vertices[idx].x;
		}
		if (xMax < vertices[idx].x)
		{
			xMax = vertices[idx].x;
		}
		if (yMin > vertices[idx].y)
		{
			yMin = vertices[idx].y;
		}
		if (yMax < vertices[idx].y)
		{
			yMax = vertices[idx].y;
		}
	}
	if (p.x < xMin || p.x > xMax || p.y < yMin || p.y > yMax)
	{
		return false;
	}

	// 2. Draw a virtual ray from anywhere outside the polygon to the point 
	//    and count how often it hits any side of the polygon. 
	//    If the number of hits is even, it's outside of the polygon, if it's odd, it's inside.
	int numberOfIntersectionPoints{ 0 };
	glm::vec2 p2{ xMax + 10.0f, p.y }; // Horizontal line from point to point outside polygon (p2)

	// Count the number of intersection points
	float lambda1{}, lambda2{};
	for (size_t i{ 0 }; i < nrVertices; ++i)
	{
		if (IntersectLineSegments(vertices[i], vertices[(i + 1) % nrVertices], p, p2, lambda1, lambda2))
		{
			if (lambda1 > 0 && lambda1 <= 1 && lambda2 > 0 && lambda2 <= 1)
			{
				++numberOfIntersectionPoints;
			}
		}
	}
	if (numberOfIntersectionPoints % 2 == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool GeoUtils::IsOverlapping(const glm::vec2& a, const glm::vec2& b, const SDL_Rect& r)
{
	if (GeoUtils::IsPointInRect(a, r) || GeoUtils::IsPointInRect(b, r))
	{
		return true;
	}
	HitInfo hitInfo{};
	glm::vec2 vertices[]{ glm::vec2 {r.x,  r.y},
		glm::vec2{ r.x + r.w, r.y },
		glm::vec2{ r.x + r.w, r.y+ r.h },
		glm::vec2{ r.x, r.y + r.h } };

	return Raycast(vertices, 4, a, b, hitInfo);
}

bool GeoUtils::IsOverlapping(const SDL_Rect& r1, const SDL_Rect& r2)
{
	// If one rectangle is on left side of the other
	if ((r1.x + r1.w) < r2.x || (r2.x + r2.w) < r1.x)
	{
		return false;
	}

	// If one rectangle is under the other
	if (r1.y > (r2.y + r2.h) || r2.y > (r1.y + r1.h))
	{
		return false;
	}

	return true;
}

bool GeoUtils::IntersectLineSegments(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& q1, const glm::vec2& q2, float& outLambda1, float& outLambda2, float epsilon)
{
	bool intersecting{ false };

	glm::vec2 p1p2{ p2.x - p1.x, p2.y - p1.y };
	glm::vec2 q1q2{ q2.x - q1.x, q2.y - q1.y };

	
	// Cross product to determine if parallel
	const float denom = GeoUtils::cross(p1p2,q1q2);

	// Don't divide by zero
	if (std::abs(denom) > epsilon)
	{
		intersecting = true;

		const glm::vec2 p1q1{ p2.x - p1.x, q2.y - q1.y };

		const float num1 = GeoUtils::cross(p1q1,q1q2);
		const float num2 = GeoUtils::cross(p1q1,p1p2);
		outLambda1 = num1 / denom;
		outLambda2 = num2 / denom;
	}
	else // are parallel
	{
		// Connect start points
		glm::vec2 p1q1{ p2.x - p1.x, q2.y - q1.y };

		// Cross product to determine if segments and the line connecting their start points are parallel, 
		// if so, than they are on a line
		// if not, then there is no intersection
		if (std::abs(GeoUtils::cross(p1q1,q1q2)) > epsilon)
		{
			return false;
		}

		// Check the 4 conditions
		outLambda1 = 0;
		outLambda2 = 0;
		if (GeoUtils::IsPointOnLineSegment(p1, q1, q2) ||
			GeoUtils::IsPointOnLineSegment(p2, q1, q2) ||
			GeoUtils::IsPointOnLineSegment(q1, p1, p2) ||
			GeoUtils::IsPointOnLineSegment(q2, p1, p2))
		{
			intersecting = true;
		}
	}
	return intersecting;
}

bool GeoUtils::IsPointOnLineSegment(const glm::vec2& p, const glm::vec2& a, const glm::vec2& b)
{
	glm::vec2 ap{ p.x - a.x, p.y - a.y }, bp{ p.x - b.x, p.y - b.y };
	// If not on same line, return false
	if (abs(GeoUtils::cross(ap,bp)) > 0.001f)
	{
		return false;
	}

	// Both vectors must point in opposite directions if p is between a and b
	if (glm::dot(ap,bp) > 0)
	{
		return false;
	}

	return true;
}

bool GeoUtils::Raycast(const std::vector<glm::vec2>& vertices, const glm::vec2& rayP1, const glm::vec2& rayP2, HitInfo& hitInfo)
{
	return Raycast(vertices.data(), vertices.size(), rayP1, rayP2, hitInfo);
}

bool GeoUtils::Raycast(const glm::vec2* vertices, const size_t nrVertices, const glm::vec2 rayP1, const glm::vec2& rayP2, HitInfo& hitInfo)
{
	if (nrVertices == 0)
	{
		return false;
	}

	std::vector<HitInfo> hits;

	SDL_Rect r1, r2;
	// r1: minimal AABB rect enclosing the ray
	r1.x = std::min((int)rayP1.x, (int)rayP2.x);
	r1.y = std::min((int)rayP1.y, (int)rayP2.y);
	r1.w = std::max((int)rayP1.x, (int)rayP2.x) - r1.x;
	r1.h = std::max((int)rayP1.y, (int)rayP2.y) - r1.y;

	// Line-line intersections.
	for (size_t idx{ 0 }; idx <= nrVertices; ++idx)
	{
		// Consider line segment between 2 consecutive vertices
		// (modulo to allow closed polygon, last - first vertice)
		glm::vec2 q1 = vertices[(idx + 0) % nrVertices];
		glm::vec2 q2 = vertices[(idx + 1) % nrVertices];

		// r2: minimal AABB rect enclosing the 2 vertices
		r2.x = std::min((int)q1.x, (int)q2.x);
		r2.y = std::min((int)q1.y, (int)q2.y);
		r2.w = std::max((int)q1.x, (int)q2.x) - r2.x;
		r2.h = std::max((int)q1.y, (int)q2.y) - r2.y;

		if (IsOverlapping(r1, r2))
		{
			float lambda1{};
			float lambda2{};
			if (IntersectLineSegments(rayP1, rayP2, q1, q2, lambda1, lambda2))
			{
				if (lambda1 > 0 && lambda1 <= 1 && lambda2 > 0 && lambda2 <= 1)
				{
					HitInfo linesHitInfo{};
					linesHitInfo.lambda = lambda1;
					linesHitInfo.intersectPoint = glm::vec2{ rayP1.x + ((rayP2.x - rayP1.x) * lambda1), rayP1.y + ((rayP2.y - rayP1.y) * lambda1) };
					auto norm = glm::vec2{ q2 - q1 };
					linesHitInfo.normal = glm::vec2(glm::normalize(glm::vec2{ -norm.y, norm.x }));
					hits.push_back(linesHitInfo);
				}
			}
		}
	}

	if (hits.empty())
	{
		return false;
	}

	// Get closest intersection point and copy it into the hitInfo parameter
	hitInfo = *std::min_element
	(
		hits.begin(), hits.end(),
		[](const HitInfo& first, const HitInfo& last)
		{
			return first.lambda < last.lambda;
		}
	);
	return true;
}
