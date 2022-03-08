#pragma once
//-----------------------------------------------------------------------------
// MathManager.h
// Utility function for math operations
//-----------------------------------------------------------------------------

class MathManager
{
public:
	static int RandInt(int startInclusive, int endInclusive);
	static double LerpD(double a, double b, double factor);
	static double LerpRad(double a, double b, double factor);
	static float AngleToRad(float angle);
private:
	MathManager() {}
};