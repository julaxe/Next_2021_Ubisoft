//-----------------------------------------------------------------------------
// DebugManager.cpp
// Contains all the debug functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include "DebugManager.h"
#include "app.h"
#include "Basics.h"

void DebugManager::DrawLine(const CVertex start, const CVertex end, const CColor col)
{
	App::DrawLine(start.x, start.y, end.x, end.y, col.r, col.g, col.b);
}

void DebugManager::QueueLine(const CVertex start, const CVertex end, const CColor col)
{
	s_points.push_back(start);
	s_points.push_back(end);
	s_colors.push_back(col);
}

void DebugManager::FlushLines()
{
	for (unsigned i = 0, j = 0; i < s_points.size(); i+=2, j++)
		DrawLine(s_points[i], s_points[i+1], s_colors[j]);
	Quit(); // Clears out vectors.
}

void DebugManager::DrawRect(CRect rect , CColor color)
{
	//0----------1
	//|			 |
	//|			 |
	//|			 |
	//3----------2
	CVertex v0 = CVertex(rect.x - rect.w * 0.5f, rect.y + rect.h * 0.5f);
	CVertex v1 = CVertex(rect.x + rect.w * 0.5f, rect.y + rect.h * 0.5f);
	CVertex v2 = CVertex(rect.x + rect.w * 0.5f, rect.y - rect.h * 0.5f);
	CVertex v3 = CVertex(rect.x - rect.w * 0.5f, rect.y - rect.h * 0.5f);

	DrawLine(v0, v1, color);
	DrawLine(v1, v2, color);
	DrawLine(v2, v3, color);
	DrawLine(v3, v0, color);
}


void DebugManager::Quit()
{
	s_points.clear();
	s_colors.clear();
	s_points.shrink_to_fit();
	s_colors.shrink_to_fit();
}

bool DebugManager::s_debugMode = false;
std::vector<CVertex> DebugManager::s_points;
std::vector<CColor> DebugManager::s_colors;