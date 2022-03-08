#pragma once
//-----------------------------------------------------------------------------
// Node.h
// Node that allow to know the possible paths for the enemy and where to put towers.
//-----------------------------------------------------------------------------
#define NODE_SIZE (64.f)

struct CVertex;
struct CRect;
struct CColor;

class CNode{
public:
	CNode() = default;
	CNode(float x, float y, int gridX, int gridY);
	~CNode();
	void DrawNode();
	void setWalkability(bool walkability) { m_walkable = walkability; }
	bool isWalkable() { return m_walkable; }
	CVertex* getPosition() { return m_position; }
	CRect* getCollisionBox() { return m_collisionBox; }
	int getFCost() { return gCost + hCost; }

	bool operator>(CNode &b);
	bool operator<(CNode &b);

public:
	int gCost;
	int hCost;
	int gridX;
	int gridY;

	CNode* parent;

private:
	CVertex* m_position;
	CColor* m_color;
	CRect* m_collisionBox;
	bool m_walkable;
};