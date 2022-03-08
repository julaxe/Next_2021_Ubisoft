//-----------------------------------------------------------------------------
// Enemy1.cpp
// Creates an enemy1
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include "Enemy2.h"
#include "Polygon.h"
#include "Node.h"
#include "MathManager.h"

CEnemy2::CEnemy2(CNode* node) : CEnemy(node)
{
	m_hp = 90.0f;
	m_currentHp = m_hp;
	m_speed = 0.5f;
	m_radius = 30.f;
	CreateShape();
}

CEnemy2::~CEnemy2()
{
	delete m_shapeBiCircle;
	delete m_shapeWheel1;
	delete m_shapeWheel2;
	delete m_shapeWheel3;
	delete m_shapeWheel4;
}

void CEnemy2::Draw()
{
	if (m_active)
	{
		m_shapeBiCircle->Draw();
		m_shapeWheel1->Draw();
		m_shapeWheel2->Draw();
		m_shapeWheel3->Draw();
		m_shapeWheel4->Draw();
	}
}

void CEnemy2::Update()
{
	FollowPath();
}

void CEnemy2::SetPosition(float x, float y)
{
	m_position = CVertex(x, y);
	m_shapeBiCircle->SetPosition(x, y);
	SetWheel(m_shapeWheel1, 45.0f);
	SetWheel(m_shapeWheel2, 135.0f);
	SetWheel(m_shapeWheel3, 225.f);
	SetWheel(m_shapeWheel4, 315.f);
	
}

void CEnemy2::SetColor(CColor color)
{
	m_color = color;
	m_shapeBiCircle->SetColor(m_color);
	m_shapeWheel1->SetColor(m_color);
	m_shapeWheel2->SetColor(m_color);
	m_shapeWheel3->SetColor(m_color);
	m_shapeWheel4->SetColor(m_color);
}

void CEnemy2::Reset()
{
	m_hp = 90.0f;
	m_currentHp = m_hp;
	setColorUpgrade(CColor());
	SetColor(CColor());
}

void CEnemy2::SetWheel(CPolygon* wheel, float offSetAngle)
{
	float angleRad = MathManager::AngleToRad(offSetAngle);
	float c1X = m_position.x + cosf(m_angle + angleRad) * m_radius;
	float c1Y = m_position.y + sinf(m_angle + angleRad) * m_radius;
	wheel->SetPosition(c1X, c1Y);
}

void CEnemy2::CreateShape()
{
	m_shapeBiCircle = new CPolygon(20, m_radius, m_color);
	m_shapeWheel1 = new CPolygon(20, m_radius * 0.2f, m_color);
	m_shapeWheel2 = new CPolygon(20, m_radius * 0.2f, m_color);
	m_shapeWheel3 = new CPolygon(20, m_radius * 0.2f, m_color);
	m_shapeWheel4 = new CPolygon(20, m_radius * 0.2f, m_color);
	SetPosition(m_currentNode->getPosition()->x, m_currentNode->getPosition()->y);
}
