//-----------------------------------------------------------------------------
// PathFindingManager.cpp
// Utility functions for path finding operations
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include "PathFindingManager.h"
#include "Node.h"
#include "Board.h"
#include <math.h>
#include <algorithm>

std::vector<CNode*> PathFindingManager::FindPath(CNode* start, CNode* target)
{
	std::vector<CNode*> openSet;
	std::make_heap(openSet.begin(), openSet.end(), [](CNode* a, CNode* b) {return *a < *b; });
	std::unordered_set<CNode*> closedSet;

	openSet.push_back(start);
	std::push_heap(openSet.begin(), openSet.end(), [](CNode* a, CNode* b) {return *a < *b; });

	while (openSet.size() > 0)
	{
		CNode* currentNode = openSet.back();
		openSet.pop_back();
		closedSet.emplace(currentNode);

		if (currentNode == target)
		{
			return RetracePath(start, target);
		}

		for (CNode* neighbour : CBoard::getInstance().GetNeighbours(currentNode))
		{
			if (!neighbour->isWalkable() || closedSet.find(neighbour) != closedSet.end())
			{
				continue;
			}

			int newMCostToNeighbour = currentNode->gCost + GetDistance(currentNode, neighbour);

			if (newMCostToNeighbour < neighbour->gCost || (std::find(openSet.begin(), openSet.end(), neighbour) == openSet.end()))
			{
				neighbour->gCost = newMCostToNeighbour;
				neighbour->hCost = GetDistance(neighbour, target);
				neighbour->parent = currentNode;

				if (std::find(openSet.begin(), openSet.end(), neighbour) == openSet.end())
				{
					openSet.push_back(neighbour);
					std::push_heap(openSet.begin(), openSet.end(), [](CNode* a, CNode* b) {return *a < *b; });
				}
			}
		}
	}
	std::vector<CNode*> emptyPath;
	return emptyPath;
}

int PathFindingManager::GetDistance(CNode* nodeA, CNode* nodeB)
{
	int dstX = abs(nodeA->gridX - nodeB->gridX);
	int dstY = abs(nodeA->gridY - nodeB->gridY);

	if (dstX > dstY)
	{
		return 14 * dstY + 10 * (dstX - dstY); // 14 and 10 are arbitrary
	}
	else
	{
		return 14 * dstY + 10 * (dstY - dstX);
	}
}

std::vector<CNode*> PathFindingManager::RetracePath(CNode* start, CNode* end)
{
	std::vector<CNode*> path;
	CNode* currentNode = end;

	while (currentNode != start)
	{
		path.push_back(currentNode);
		currentNode = currentNode->parent;
	}
	return path;
}
