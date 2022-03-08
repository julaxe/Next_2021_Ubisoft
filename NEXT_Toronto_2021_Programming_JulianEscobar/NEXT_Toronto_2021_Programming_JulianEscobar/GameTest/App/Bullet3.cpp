//-----------------------------------------------------------------------------
// Bullet.cpp
// first type of bullets
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include "Bullet3.h"
#include "Polygon.h"
#include "MathManager.h"
CBullet3::CBullet3() : CBullet()
{
	m_color = CColor(0.5f,1.0f, 1.0f);
	m_damage = 5.0f;
	m_radius = 16.f;
	m_speed = 1.0f;
	CreateShape();
}

void CBullet3::Draw()
{
	if (m_active)
	{
		m_shapeRectangle->Draw();
	}
}

void CBullet3::Update(float deltatime)
{
	if (m_active)
	{
		checkCollisionWithEnemies();
		checkScreenBorders();
		m_position = m_position + (m_direction * m_speed);
		SetPosition(m_position.x, m_position.y);
		m_angleRotation += MathManager::AngleToRad(1.0f);
		m_shapeRectangle->Rotate(m_angleRotation);
	}
}

void CBullet3::SetPosition(float x, float y)
{
	m_shapeRectangle->SetPosition(x, y);
}

void CBullet3::CreateShape()
{
	m_shapeRectangle = new CPolygon(6, m_radius, m_color);
}
