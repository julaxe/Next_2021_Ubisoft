#pragma once
//-----------------------------------------------------------------------------
// PathFindingManager.h
// Utility functions for path finding operations
//-----------------------------------------------------------------------------
#include <unordered_set>
struct CVertex;
class CNode;
class PathFindingManager
{
public:
	static std::vector<CNode*> FindPath(CNode* start, CNode* target);
	static int GetDistance(CNode* nodeA, CNode* nodeB);
	static std::vector<CNode*> RetracePath(CNode* start, CNode* end);
	

private:
	PathFindingManager() {} 
};

