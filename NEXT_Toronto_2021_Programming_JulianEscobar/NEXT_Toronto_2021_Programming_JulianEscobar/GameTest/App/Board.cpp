///////////////////////////////////////////////////////////////////////////////
// Filename: Board.cpp
// The Stage that contains the Nodes.
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include "Board.h"
#include "app.h"
#include "Basics.h"
#include "CollisionManager.h"
#include "MathManager.h"
#include "Node.h"
#include "DebugManager.h"
#include "Polygon.h"

#define _USE_MATH_DEFINES
#include <math.h>




//std::array<std::array<CNode*, COLS>, ROWS> CBoard::grid;
CBoard::CBoard()
{
	m_rows = ROWS;
	m_cols = COLS;

	CreateBackgroundRect();
	CreateGrid();
}

CBoard::~CBoard()
{
	delete m_Rect1;
	delete m_Rect2;
	delete m_Rect3;
}

void CBoard::Draw()
{
	m_Rect1->Draw();
	m_Rect2->Draw();
	m_Rect3->Draw();

	for (int x = 0; x < m_cols; x++)
	{
		for (int y = 0; y < m_rows; y++)
		{
			grid[y][x]->DrawNode();
		}
	}

	DebugManager::DrawRect(*startPoint->getCollisionBox(), { 0.0f, 1.0f, 0.0f });
	DebugManager::DrawRect(*finishPoint->getCollisionBox(), { 0.1f, 0.3f, 1.0f });
}

void CBoard::Update()
{
	path = PathFindingManager::FindPath(getStartPoint(), getFinishPoint());
}

std::vector<CNode*> CBoard::GetNeighbours(CNode* node)
{
	std::vector<CNode*> neighbours;
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			if (x ==0 && y == 0) //no itself
				continue;
			if (x != 0 && y != 0) // no corners
				continue;

			int checkX = node->gridX + x;
			int checkY = node->gridY + y;

			if (checkX >= 0 && checkX < m_cols && checkY >= 0 && checkY < m_rows)
			{
				neighbours.push_back(grid[checkY][checkX]);
			}
		}
	}
	return neighbours;
}
CNode* CBoard::GetNodeFromWorldPosition(CVertex worldPosition)
{
	float percentX = worldPosition.x / NODE_SIZE;
	float percentY = worldPosition.y / NODE_SIZE;

	int x = (int)percentX;
	int y = (int)percentY;

	return grid[y][x];

}
void CBoard::CreateGrid() 
{
	for (int x = 0; x < m_cols; x++)
	{
		for (int y = 0; y < m_rows; y++)
		{
			float worldPosX = (x * NODE_SIZE) + (NODE_SIZE / 2);
			float worldPosY = (y * NODE_SIZE) + (NODE_SIZE / 2);
			grid[y][x] = new CNode(worldPosX, worldPosY, x, y);
			if (!CheckCollisionWithRectangles(worldPosX, worldPosY))
			{
				grid[y][x]->setWalkability(false);
			}
		}
	}

	//calculate startPoint
	CVertex leftBottomCorner = CVertex(m_Rect1->getRect().x - m_Rect1->getRect().w * 0.5f + 1,
		m_Rect1->getRect().y - m_Rect1->getRect().h * 0.5f + 1);
	startPoint = GetNodeFromWorldPosition(leftBottomCorner);

	//calculate finishPoint
	CVertex rightTopCorner = CVertex(m_Rect3->getRect().x + m_Rect3->getRect().w * 0.5f - 1,
		m_Rect3->getRect().y + m_Rect3->getRect().h * 0.5f - 1);
	finishPoint = GetNodeFromWorldPosition(rightTopCorner);
}


bool CBoard::CheckCollisionWithRectangles(float x, float y)
{
	CVertex vertex = CVertex(x, y);
	if (CollisionManager::VertexInsideRect(vertex, m_Rect1->getRect()))
	{
		return true;
	}
	if (CollisionManager::VertexInsideRect(vertex, m_Rect2->getRect()))
	{
		return true;
	}
	if (CollisionManager::VertexInsideRect(vertex, m_Rect3->getRect()))
	{
		return true;
	}
	return false;
}

void CBoard::CreateBackgroundRect()
{
	m_Rect1 = App::CreateSprite(".\\TestData\\dark_blue.bmp", 1, 1);
	m_Rect3 = App::CreateSprite(".\\TestData\\dark_blue.bmp", 1, 1);

	m_Rect2 = new CSimpleSprite(*m_Rect1);

	float randY = ((float)MathManager::RandInt(-2, 2) * NODE_SIZE) + APP_VIRTUAL_HEIGHT/2.0f;
	m_Rect1->SetPosition(APP_VIRTUAL_WIDTH / 4, randY);

	randY = ((float)MathManager::RandInt(-2, 2) * NODE_SIZE) + APP_VIRTUAL_HEIGHT/2.0f;
	m_Rect2->SetPosition(APP_VIRTUAL_WIDTH / 2, randY);

	randY = ((float)MathManager::RandInt(-2, 2) * NODE_SIZE) + APP_VIRTUAL_HEIGHT / 2.0f;
	m_Rect3->SetPosition((3*APP_VIRTUAL_WIDTH/4), randY);

	

}
