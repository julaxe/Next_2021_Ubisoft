//-----------------------------------------------------------------------------
// Turret1.cpp
// Creates  Turret 1
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include "Turret1.h"
#include "Polygon.h"
#include "Basics.h"
#include "Node.h"
#include "EnemiesPool.h"
#include "BulletPool.h"
#include "app.h"

CTurret1::CTurret1(CNode* node) : CTurret(node)
{
	m_cost = 10;
	m_level = 1;
	CreateShape();
	m_range = 300.0f;
}

CTurret1::~CTurret1()
{
	delete m_shapeCircle;
	delete m_shapeTriangle;
	delete m_shapeMiniCircle;
}

void CTurret1::Draw()
{
	if (m_active)
	{
		m_shapeCircle->Draw();
		m_shapeTriangle->Draw();
		m_shapeMiniCircle->Draw();
	}
}

void CTurret1::Update(float deltaTime)
{
	if (m_active)
	{
		CVertex enemy = CEnemiesPool::getInstance().getFirstEnemyInRange(this);
		if (enemy.Magnitude() != 0.0f) //founded
		{
			Aim(enemy);
			m_shapeTriangle->Rotate(m_angle);

			//set position for head
			float cX = m_shapeTriangle->getPosition()->x + cosf(m_angle) * 16.0f;
			float cY = m_shapeTriangle->getPosition()->y + sinf(m_angle) * 16.0f;
			m_shapeMiniCircle->SetPosition(cX, cY);

			if (m_timer > m_fireRate)
			{
				Shoot();
				m_timer = 0.0f;
			}

		}
		m_timer += deltaTime / 1000.0f;
	}
}

void CTurret1::SetPosition(float x, float y)
{
	m_shapeCircle->SetPosition(x, y);
	m_shapeTriangle->SetPosition(x, y);

	//set position for head
	float cX = m_shapeTriangle->getPosition()->x + cosf(m_angle) * 16.0f;
	float cY = m_shapeTriangle->getPosition()->y + sinf(m_angle) * 16.0f;
	m_shapeMiniCircle->SetPosition(cX, cY);
}

void CTurret1::ChangeNode(CNode* node)
{
	m_node = node;
	SetPosition(m_node->getPosition()->x, m_node->getPosition()->y);
}

void CTurret1::SetColor(CColor color)
{
	*m_color = color;
	m_shapeCircle->SetColor(color);
	m_shapeTriangle->SetColor(color);
	m_shapeMiniCircle->SetColor(color);
}

void CTurret1::Shoot()
{
	CBulletPool::getInstance().Shoot1(*m_node->getPosition(), *m_front);
	App::PlaySound(".\\TestData\\shoot1.wav");
}

void CTurret1::CreateShape()
{
	m_shapeCircle = new CPolygon(20, 32.0f, *m_color);
	m_shapeTriangle = new CPolygon(3, 16.0f, *m_color);
	m_shapeMiniCircle = new CPolygon(20, 3.0f, *m_color);
	SetPosition(m_node->getPosition()->x, m_node->getPosition()->y);
}
