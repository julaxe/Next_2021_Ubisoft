//-----------------------------------------------------------------------------
// Bullet.cpp
// Base Class for bullets
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include "Bullet.h"
#include "CollisionManager.h"
#include "EnemiesPool.h"
#include "Polygon.h"
#include "app.h"

CBullet::CBullet()
{
	m_speed = 0;
	m_radius = 0.0f;
	m_color = CColor();
	m_active = false;
	m_exploded = false;
	m_shapeExplosion = new CPolygon(20, 1.0f, { 1.0f, 0.5f, 0.0f });
}

void CBullet::Activate(CVertex position, CVertex direction)
{
	m_active = true;
	m_exploded = false;
	m_position = position;
	m_direction = direction;
	SetPosition(m_position.x, m_position.y);
}

void CBullet::Desactivate()
{
	m_active = false;
	m_exploded = false;
	m_shapeExplosion->SetScale(1.0f);
}

void CBullet::DrawExplosion()
{
	m_shapeExplosion->Draw();
}

void CBullet::UpdateExplosion()
{
	float scale = m_shapeExplosion->getScale();
	scale += 600.f / 1000.f;
	m_shapeExplosion->SetScale(scale);
	if (m_timer > 0.2f)
	{
		Desactivate();
		m_timer = 0.0f;
	}
}

bool CBullet::checkScreenBorders()
{
	if (m_position.x < -10.0f ||
		m_position.x > (float)APP_VIRTUAL_WIDTH + 10.0f ||
		m_position.y < -10.0f ||
		m_position.y >(float)APP_VIRTUAL_HEIGHT + 10.0f)
	{
		Desactivate();
		return true;
	}
	return false;
}

bool CBullet::checkCollisionWithEnemies()
{
	for (auto enemy : CEnemiesPool::getInstance().getPool1())
	{
		if (enemy->isActive())
		{
			if (CollisionManager::CircleInsideCircle(m_position, m_radius, enemy->getPosition(), enemy->getRadius()))
			{
				m_exploded = true;
				m_timer = 0.0f;
				m_shapeExplosion->SetPosition(m_position.x, m_position.y);

				//to Enemy
				enemy->TakeDamage(m_damage);
				return true;
			}
		}
	}
	for (auto enemy : CEnemiesPool::getInstance().getPool2())
	{
		if (enemy->isActive())
		{
			if (CollisionManager::VertexInsideCircle(m_position, enemy->getPosition(), enemy->getRadius()))
			{
				m_exploded = true;
				m_timer = 0.0f;
				m_shapeExplosion->SetPosition(m_position.x, m_position.y);

				//to Enemy
				enemy->TakeDamage(m_damage);
				return true;
			}
		}
	}
	for (auto enemy : CEnemiesPool::getInstance().getPool3())
	{
		if (enemy->isActive())
		{
			if (CollisionManager::VertexInsideCircle(m_position, enemy->getPosition(), enemy->getRadius()))
			{
				m_exploded = true;
				m_timer = 0.0f;
				m_shapeExplosion->SetPosition(m_position.x, m_position.y);

				//to Enemy
				enemy->TakeDamage(m_damage);
				return true;
			}
		}
	}
	return false;
}
