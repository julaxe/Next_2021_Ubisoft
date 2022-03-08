///////////////////////////////////////////////////////////////////////////////
// Filename: CollisionManager.cpp
// Functions that help to detect collision between objects
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include "CollisionManager.h"
#include "Basics.h"

bool CollisionManager::VertexInsideRect(CVertex vertex, CRect rect)
{
	if (vertex.x >= rect.x - rect.w / 2 &&
		vertex.x <= rect.x + rect.w / 2 &&
		vertex.y >= rect.y - rect.h / 2 &&
		vertex.y <= rect.y + rect.h / 2)
	{
		return true;
	}
	return false;
}

bool CollisionManager::VertexInsideCircle(CVertex vertex, CVertex circleP, float radius)
{
	CVertex distance = circleP - vertex;
	float d = distance.Magnitude();
	if (d <= radius)
	{
		return true;
	}
	return false;
}

bool CollisionManager::CircleInsideCircle(CVertex a, float radiusA, CVertex b, float radiusB)
{
	CVertex distance = a - b;
	float d = distance.Magnitude();
	if (d <= radiusA + radiusB)
	{
		return true;
	}
	return false;
}

bool CollisionManager::RectWithRect(CRect a, CRect b)
{
	float aX = a.x - a.w / 2;
	float aY = a.y - a.h / 2;
	float bX = b.x - b.w / 2;
	float bY = b.y - b.h / 2;
	if (aX < bX + b.w &&
		aX + a.w > bX &&
		aY < bY + b.h &&
		aY + a.h > bY)
	{
		return true;
	}
	return false;
}
