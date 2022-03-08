//-----------------------------------------------------------------------------
// Bullet.cpp
// first type of bullets
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include "Bullet1.h"
#include "Polygon.h"
CBullet1::CBullet1() : CBullet()
{
	m_damage = 5.0f;
	m_radius = 4.0f;
	m_speed = 2.0f;
	CreateShape();
}

void CBullet1::Draw()
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

void CBullet1::Update(float deltatime)
{
	if (m_active)
	{
		if (!m_exploded)
		{
			if (!checkScreenBorders() && !checkCollisionWithEnemies())
			{
				m_position = m_position + (m_direction * m_speed);
				SetPosition(m_position.x, m_position.y);
			}
		}
		else
		{
			UpdateExplosion();
		}
		m_timer += deltatime / 1000.f;
	}
}

void CBullet1::SetPosition(float x, float y)
{
	m_shapeRectangle->SetPosition(x, y);
}

void CBullet1::CreateShape()
{
	m_shapeRectangle = new CPolygon(20, m_radius, m_color);
	m_shapeRectangle->Rotate(atan2f(m_direction.y, m_direction.x));
}
