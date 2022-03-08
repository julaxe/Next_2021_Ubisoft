#pragma once
//-----------------------------------------------------------------------------
// Board.h
// The Stage that contains the Nodes.
//-----------------------------------------------------------------------------
class CSimpleSprite;
#include "Node.h"
#include <array>
#include <vector>

#define COLS (16)
#define ROWS (12)

class CPolygon;
class CBoard {
public:
	
	static CBoard& getInstance()
	{
		static CBoard Instance;
		return Instance;
	}
	~CBoard();
	void Draw();
	void Update();
	std::vector<CNode*> GetNeighbours(CNode* node);
	CNode* GetNodeFromWorldPosition(CVertex worldPosition);
	int getMaxSize() { return m_cols * m_rows; }

	CNode* getStartPoint() { return startPoint; }
	CNode* getFinishPoint() { return finishPoint; }

	std::array<std::array<CNode*, COLS>, ROWS> grid;
	std::vector<CNode*> path;

private:

	CBoard();
	void CreateGrid();
	void CreateBackgroundRect();
	bool CheckCollisionWithRectangles(float x, float y);

	int m_rows;
	int m_cols;

	CNode* startPoint;
	CNode* finishPoint;
	
	CSimpleSprite* m_Rect1;
	CSimpleSprite* m_Rect2;
	CSimpleSprite* m_Rect3;
};