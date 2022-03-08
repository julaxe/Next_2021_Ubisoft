#pragma once
//-----------------------------------------------------------------------------
// Bullet.h
// Base Class for bullets
//-----------------------------------------------------------------------------
#include "Basics.h"
class CPolygon;
class CBullet
{
public:
	CBullet();
	virtual void Draw() {};
	virtual void Update(float deltatime) {};
	virtual void SetPosition(float x, float y) {};
	bool isActive() { return m_active; }
	void Activate(CVertex position, CVertex direction);
	void Desactivate();

	void DrawExplosion();
	void UpdateExplosion();

	bool checkScreenBorders();
	bool checkCollisionWithEnemies();
protected:

	float m_radius;
	float m_damage;
	float m_timer;
	bool m_exploded;
	bool m_active;
	CVertex m_position;
	CVertex m_direction;
	float m_speed;
	CColor m_color;

	CPolygon* m_shapeExplosion;
};