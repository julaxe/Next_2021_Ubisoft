//-----------------------------------------------------------------------------
// Enemy1.cpp
// Creates an enemy1
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include "Enemy1.h"
#include "Polygon.h"
#include "Node.h"

CEnemy1::CEnemy1(CNode* node) : CEnemy(node)
{
	m_hp = 15.0f;
	m_currentHp = m_hp;
	m_speed = 1.0f;
	m_radius = 16.f;
	CreateShape();
}

CEnemy1::~CEnemy1()
{
	delete m_shapeCircle1;
	delete m_shapeCircle2;
}

void CEnemy1::Draw()
{
	if (m_active)
	{
		m_shapeCircle1->Draw();
		m_shapeCircle2->Draw();
	}
}

void CEnemy1::Update()
{
	FollowPath();
}

void CEnemy1::SetPosition(float x, float y)
{
	m_position = CVertex(x, y);
	m_shapeCircle1->SetPosition(x, y);
	float c2X = x + cosf(m_angle) * m_radius;
	float c2Y = y + sinf(m_angle) * m_radius;
	m_shapeCircle2->SetPosition(c2X, c2Y);
}

void CEnemy1::SetColor(CColor color)
{
	m_color = color;
	m_shapeCircle1->SetColor(m_color);
	m_shapeCircle2->SetColor(m_color);
}

void CEnemy1::Reset()
{
	m_hp = 15.0f;
	m_currentHp = m_hp;
	setColorUpgrade(CColor());
	SetColor(CColor());
}

void CEnemy1::CreateShape()
{
	m_shapeCircle1 = new CPolygon(20, m_radius, m_color);
	m_shapeCircle2 = new CPolygon(20, m_radius*0.5f, m_color);
	SetPosition(m_currentNode->getPosition()->x, m_currentNode->getPosition()->y);
}
