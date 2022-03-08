#pragma once
//-----------------------------------------------------------------------------
// Basics.h
// Contains all the basics structures like vertex and squares and colors
//-----------------------------------------------------------------------------

#include <math.h>
struct CVertex
{
	CVertex() = default;
	CVertex(float x, float y) { this->x = x; this->y = y; }
	float x;
	float y;
	void Move(float dx, float dy) { x += dx; y += dy; }
	float Magnitude() { return sqrtf(x * x + y * y); }
	CVertex ConvertToUnit() { return CVertex(*this / Magnitude()); }

	CVertex operator+(CVertex& b)
	{
		return CVertex(this->x + b.x, this->y + b.y);
	}
	CVertex operator-(CVertex& b)
	{
		return CVertex(this->x - b.x, this->y - b.y);
	}
	CVertex operator*(float b)
	{
		return CVertex(this->x * b, this->y * b);
	}
	CVertex operator/(float b)
	{
		return CVertex(this->x / b, this->y / b);
	}

};

struct CColor
{
	CColor() { r = 1.0f; g = 1.0f; b = 1.0f; }
	~CColor() {}
	CColor(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }
	float r;
	float g;
	float b;

	bool operator==(CColor& other)
	{
		if (this->r == other.r &&
			this->g == other.g &&
			this->b == other.b)
		{
			return true;
		}
		return false;
	}
};

struct CRect
{
	CRect() = default;
	CRect(float x, float y, float w, float h) { this->x = x; this->y = y; this->w = w; this->h = h; }
	float x;
	float y;
	float w;
	float h;
};