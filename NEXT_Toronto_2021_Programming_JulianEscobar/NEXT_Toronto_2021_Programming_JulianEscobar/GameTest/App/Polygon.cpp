//---------------------------------------------------------------------------------
// App.cpp
// Implementation of the calls that are exposed via the App namespace.
//---------------------------------------------------------------------------------
#include "stdafx.h"
//---------------------------------------------------------------------------------
#include "Polygon.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "DebugManager.h"
#include "Basics.h"

CPolygon::CPolygon(int Nsides, float scale, CColor color)
{
	m_iNumberOfSides = Nsides;
	m_fScale = scale;
	m_color = new CColor(color);
	m_position = new CVertex(0.0f, 0.0f);
	CreatePolygon();
	m_angle = 0.0f;
	
}

CPolygon::~CPolygon()
{
	delete m_color;

	for (int i = 0; i < vertices.size(); i++)
	{
		delete vertices[i];
	}
}

void CPolygon::Move(float dx, float dy)
{
	*m_position = *m_position + CVertex(dx, dy);

	for (auto vertex : vertices)
	{
		vertex->x += dx;
		vertex->y += dy;
	}
}

void CPolygon::SetPosition(float x, float y)
{
	*m_position = CVertex(x, y);
	Rotate(m_angle);
}

void CPolygon::Draw()
{
	for (int i = 0; i < m_iNumberOfSides - 1; i++)
	{
		DebugManager::DrawLine(*vertices[i], *vertices[i + 1], *m_color);
	}
	//Last line
	DebugManager::DrawLine(*vertices[m_iNumberOfSides - 1], *vertices[0], *m_color);
}

void CPolygon::Rotate(float angle)
{
	CVertex oldPosition = *m_position;
	m_angle = angle;
	ClearVertices();
	CreatePolygon(); //with new angle
	Move(oldPosition.x, oldPosition.y);

}

void CPolygon::SetColor(CColor color)
{
	*m_color = color;
}

void CPolygon::SetScale(float scale)
{
	m_fScale = scale;
	CVertex oldPosition = *m_position;
	ClearVertices();
	CreatePolygon(); //with new scale
	Move(oldPosition.x, oldPosition.y);
}

void CPolygon::ClearVertices()
{
	vertices.clear();
}

void CPolygon::CreatePolygon()
{
	*m_position = CVertex(0.0f, 0.0f);
	float angle = 2.0f * (float)M_PI / (float)m_iNumberOfSides;
	for (int i = 0; i < m_iNumberOfSides; i++)
	{
		float tempAngle = (angle * (i)) + m_angle;
		vertices.push_back(new CVertex(cosf(tempAngle) * m_fScale, sinf(tempAngle) * m_fScale));
	}
}