//-----------------------------------------------------------------------------
// Bullet.cpp
// first type of bullets
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include "Bullet2.h"
#include "Polygon.h"
#include "MathManager.h"
CBullet2::CBullet2() : CBullet()
{
	m_color = CColor(0.9f, 0.5f, 1.0f);
	m_radius = 4.0f;
	m_damage = 15.0f;
	m_speed = 4.0f;
	CreateShape();
}

void CBullet2::Draw()
{
	if (m_active)
	{
		if (m_exploded)
		{
			DrawExplosion();
			return;
		}
		else
		{
			m_shapeRectangle->Draw();
		}
	}
}

void CBullet2::Update(float deltatime)
{
	if (m_active)
	{
		if (!m_exploded)
		{
			if (!checkScreenBorders() && !checkCollisionWithEnemies())
			{
				m_position = m_position + (m_direction * m_speed);
				SetPosition(m_position.x, m_position.y);
				m_angleRotation += MathManager::AngleToRad(8.0f);
				m_shapeRectangle->Rotate(m_angleRotation);
			}
		}
		else
		{
			UpdateExplosion();
		}
		m_timer += deltatime / 1000.f;
	}
}

void CBullet2::SetPosition(float x, float y)
{
	m_shapeRectangle->SetPosition(x, y);
}

void CBullet2::CreateShape()
{
	m_shapeRectangle = new CPolygon(4, m_radius, m_color);
}
