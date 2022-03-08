//-----------------------------------------------------------------------------
// DebugManager.h
// Contains all the debug functions
//-----------------------------------------------------------------------------
#pragma once
struct CVertex;
struct CRect;
class CollisionManager
{
public:
	static bool VertexInsideRect(CVertex vertex, CRect rect);
	static bool VertexInsideCircle(CVertex a, CVertex circleP, float radius);
	static bool CircleInsideCircle(CVertex a, float radiusA, CVertex b, float radiusB);
	static bool RectWithRect(CRect a, CRect b);
private:
	CollisionManager() {}
};
