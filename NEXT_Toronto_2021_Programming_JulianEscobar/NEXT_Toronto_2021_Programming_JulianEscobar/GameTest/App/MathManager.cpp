//-----------------------------------------------------------------------------
// MathManager.cpp
// Utility function for math operations
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include "MathManager.h"
#include <stdlib.h>

#define _USE_MATH_DEFINES

#include <math.h>


int MathManager::RandInt(int startInclusive, int endInclusive)
{
	int Range = (endInclusive - startInclusive) + 1; // +1 because is inclusive
	int rNumber = (rand() % Range) + startInclusive;
	return rNumber;
}

double MathManager::LerpD(double a, double b, double factor)
{
	return ((1.0 - factor) * a) + (factor * b);
}

double MathManager::LerpRad(double a, double b, double factor)
{
	return 0.0;
}

float MathManager::AngleToRad(float angle)
{
	return angle * ((float)M_PI / 180.0f);
}
