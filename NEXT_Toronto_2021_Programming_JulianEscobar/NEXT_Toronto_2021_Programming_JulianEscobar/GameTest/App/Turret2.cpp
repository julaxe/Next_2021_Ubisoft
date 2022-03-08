//-----------------------------------------------------------------------------
// Turret1.cpp
// Creates  Turret 1
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include "Turret2.h"
#include "Polygon.h"
#include "Basics.h"
#include "Node.h"
#include "EnemiesPool.h"
#include "BulletPool.h"
#include "MathManager.h"
#include "app.h"


CTurret2::CTurret2(CNode* node) : CTurret(node)
{
	m_cost = 50;
	m_level = 2;
	CreateShape();
	m_range = 300.0f;
	SetColor({ 0.8f,0.8f,1.0f });
}

CTurret2::~CTurret2()
{
	delete m_shapeSquare;
	delete m_shapeRotatorySquare;
	delete m_shapeTriangle;
	delete m_shapeMiniCircle;
}

void CTurret2::Draw()
{
	if (m_active)
	{
		m_shapeSquare->Draw();
		m_shapeRotatorySquare->Draw();
		m_shapeTriangle->Draw();
		m_shapeMiniCircle->Draw();
	}
}

void CTurret2::Update(float deltaTime)
{
	if (m_active)
	{
		//rotate base 2
		m_angleRot += MathManager::AngleToRad(4.0f);
		m_shapeRotatorySquare->Rotate(m_angleRot);
		CVertex enemy = CEnemiesPool::getInstance().getFirstEnemyInRange(this);
		if (enemy.Magnitude() != 0.0f) //founded
		{
			Aim(enemy);
			m_shapeTriangle->Rotate(m_angle);

			//set position for head
			float cX = m_shapeTriangle->getPosition()->x + cosf(m_angle) * 13.0f;
			float cY = m_shapeTriangle->getPosition()->y + sinf(m_angle) * 13.0f;
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

void CTurret2::SetPosition(float x, float y)
{
	m_shapeSquare->SetPosition(x, y);
	m_shapeRotatorySquare->SetPosition(x, y);
	m_shapeTriangle->SetPosition(x, y);

	//set position for head
	float cX = m_shapeTriangle->getPosition()->x + cosf(m_angle) * 13.0f;
	float cY = m_shapeTriangle->getPosition()->y + sinf(m_angle) * 13.0f;
	m_shapeMiniCircle->SetPosition(cX, cY);
}

void CTurret2::ChangeNode(CNode* node)
{
	m_node = node;
	SetPosition(m_node->getPosition()->x, m_node->getPosition()->y);
}

void CTurret2::SetColor(CColor color)
{
	*m_color = color;
	m_shapeSquare->SetColor(color);
	m_shapeRotatorySquare->SetColor(color);
	
	m_shapeTriangle->SetColor(color);
	m_shapeMiniCircle->SetColor(color);
}

void CTurret2::Shoot()
{
	CBulletPool::getInstance().Shoot2(*m_node->getPosition(), *m_front);
	App::PlaySound(".\\TestData\\shoot2.wav");
}

void CTurret2::CreateShape()
{
	m_shapeSquare = new CPolygon(4, 32.0f, *m_color);
	m_shapeSquare->Rotate(MathManager::AngleToRad(45.0f));
	m_shapeRotatorySquare = new CPolygon(4, 32.0f / sqrtf(2), *m_color);


	m_shapeTriangle = new CPolygon(3, 13.0f, *m_color);
	m_shapeMiniCircle = new CPolygon(20, 3.0f, *m_color);
	SetPosition(m_node->getPosition()->x, m_node->getPosition()->y);
}
