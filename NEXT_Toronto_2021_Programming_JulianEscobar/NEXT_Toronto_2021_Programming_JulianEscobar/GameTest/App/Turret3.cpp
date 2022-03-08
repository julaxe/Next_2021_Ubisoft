//-----------------------------------------------------------------------------
// Turret1.cpp
// Creates  Turret 1
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include "Turret3.h"
#include "Polygon.h"
#include "Basics.h"
#include "Node.h"
#include "EnemiesPool.h"
#include "BulletPool.h"
#include "MathManager.h"
#include "app.h"


CTurret3::CTurret3(CNode* node) : CTurret(node)
{
	m_cost = 100;
	m_angleRot1 = 0.0f;
	m_angleRot2 = 45.0f;
	m_fireRate = 3.0f;
	m_level = 2;
	CreateShape();
	m_range = 300.0f;
	SetColor({ 0.95f,0.83f,1.0f });
}

CTurret3::~CTurret3()
{
	delete m_shapeRotatorySquare1;
	delete m_shapeRotatorySquare2;
	delete m_shapeTriangle;
	delete m_shapeMiniCircle;
}

void CTurret3::Draw()
{
	if (m_active)
	{
		m_shapeRotatorySquare1->Draw();
		m_shapeRotatorySquare2->Draw();
		m_shapeTriangle->Draw();
		m_shapeMiniCircle->Draw();
	}
}

void CTurret3::Update(float deltaTime)
{
	if (m_active)
	{
		//rotate base 2
		m_angleRot1 += MathManager::AngleToRad(4.0f);
		m_angleRot2 += MathManager::AngleToRad(8.0f);
		m_shapeRotatorySquare1->Rotate(m_angleRot1);
		m_shapeRotatorySquare2->Rotate(m_angleRot2);

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

void CTurret3::SetPosition(float x, float y)
{
	m_shapeRotatorySquare1->SetPosition(x, y);
	m_shapeRotatorySquare2->SetPosition(x, y);
	m_shapeTriangle->SetPosition(x, y);

	//set position for head
	float cX = m_shapeTriangle->getPosition()->x + cosf(m_angle) * 20.0f;
	float cY = m_shapeTriangle->getPosition()->y + sinf(m_angle) * 20.0f;
	m_shapeMiniCircle->SetPosition(cX, cY);
}

void CTurret3::ChangeNode(CNode* node)
{
	m_node = node;
	SetPosition(m_node->getPosition()->x, m_node->getPosition()->y);
}

void CTurret3::SetColor(CColor color)
{
	*m_color = color;
	m_shapeRotatorySquare1->SetColor(color);
	m_shapeRotatorySquare2->SetColor(color);

	m_shapeTriangle->SetColor(color);
	m_shapeMiniCircle->SetColor(color);
}

void CTurret3::Shoot()
{
	CBulletPool::getInstance().Shoot3(*m_node->getPosition(), *m_front);
	App::PlaySound(".\\TestData\\shoot3.wav");
}

void CTurret3::CreateShape()
{
	m_shapeRotatorySquare1 = new CPolygon(4, 16.0f / sqrtf(2), *m_color);
	m_shapeRotatorySquare2 = new CPolygon(4, 16.0f / sqrtf(2), *m_color);


	m_shapeTriangle = new CPolygon(3, 32.0f, *m_color);
	m_shapeMiniCircle = new CPolygon(20, 5.0f, *m_color);
	SetPosition(m_node->getPosition()->x, m_node->getPosition()->y);
}
