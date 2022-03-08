#pragma once
//-----------------------------------------------------------------------------
// Polygon.h
// Creates polygon depending on the amount of sides
//-----------------------------------------------------------------------------
#include <vector>
struct CVertex;
struct CColor;

class CPolygon
{
public:
	CPolygon(int Nsides, float scale, CColor color);
	~CPolygon();
	void Move(float dx, float dy);
	void SetPosition(float x, float y);
	CVertex* getPosition() { return m_position; }
	void Draw();
	void Rotate(float angle);
	void SetColor(CColor color);
	void SetScale(float scale);
	float getScale() { return m_fScale; }
	void ClearVertices();
	std::vector<CVertex*> const getVertices() { return vertices; }

private:
	void CreatePolygon();
	int m_iNumberOfSides;
	float m_fScale;
	float m_angle;
	CColor* m_color;
	CVertex* m_position;
	std::vector<CVertex*> vertices;
};