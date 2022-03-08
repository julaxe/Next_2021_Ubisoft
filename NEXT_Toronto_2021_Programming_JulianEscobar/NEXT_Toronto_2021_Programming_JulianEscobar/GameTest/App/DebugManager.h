//-----------------------------------------------------------------------------
// DebugManager.h
// Contains all the debug functions
//-----------------------------------------------------------------------------
#ifndef _DEBUGMANAGER_H_
#define _DEBUGMANAGER_H_

#include <vector>
struct CVertex;
struct CColor;
struct CRect;

class DebugManager
{
public: // Public methods.
	static bool s_debugMode;
	static void DrawLine(const CVertex start, const CVertex end, const CColor col);
	static void QueueLine(const CVertex start, const CVertex end, const CColor col);
	static void FlushLines();
	static void DrawRect(CRect rect, CColor color);
	static void Quit();
private: // Private properties.
	static std::vector<CVertex> s_points;
	static std::vector<CColor> s_colors;
private: // Public methods.
	DebugManager() {}
};


#endif