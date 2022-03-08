//-----------------------------------------------------------------------------
// Enemy1.cpp
// Creates an enemy1
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include "Enemy3.h"
#include "Polygon.h"
#include "Node.h"
#include "MathManager.h"

CEnemy3::CEnemy3(CNode* node) : CEnemy(node)
{
	m_hp = 30.0f;
	m_currentHp = m_hp;
	m_speed = 2.0f;
	m_radius = 16.f;
	CreateShape();
}

CEnemy3::~CEnemy3()
{
	delete m_shapeTriangleFront;
	delete m_shapeTriangleBack;
}

void CEnemy3::Draw()
{
	if (m_active)
	{
		m_shapeTriangleFront->Draw();
		m_shapeTriangleBack->Draw();
	}
}

void CEnemy3::Update()
{
	FollowPath();
}

void CEnemy3::SetPosition(float x, float y)
{
	m_position = CVertex(x, y);
	float c1X = x + cosf(m_angle) * (m_radius * 0.5f);
	float c1Y = y + sinf(m_angle) * (m_radius * 0.5f);
	m_shapeTriangleFront->SetPosition(c1X, c1Y);
	m_shapeTriangleFront->Rotate(m_angle);
	float c2X = x - cosf(m_angle) * (m_radius * 0.5f);
	float c2Y = y - sinf(m_angle) * (m_radius * 0.5f);
	m_shapeTriangleBack->SetPosition(c2X, c2Y);
	m_shapeTriangleBack->Rotate(m_angle + MathManager::AngleToRad(180.0f));
}

void CEnemy3::SetColor(CColor color)
{
	m_color = color;
	m_shapeTriangleFront->SetColor(m_color);
	m_shapeTriangleBack->SetColor(m_color);
}

void CEnemy3::Reset()
{
	m_hp = 30.0f;
	m_currentHp = m_hp;
	setColorUpgrade(CColor());
	SetColor(CColor());
}

void CEnemy3::CreateShape()
{
	m_shapeTriangleFront = new CPolygon(3, m_radius, m_color);
	m_shapeTriangleBack = new CPolygon(3, m_radius, m_color);
	SetPosition(m_currentNode->getPosition()->x, m_currentNode->getPosition()->y);
}
