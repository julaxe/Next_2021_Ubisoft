#pragma once
//-----------------------------------------------------------------------------
// Bullet2.h
// second type of bullets
//-----------------------------------------------------------------------------
#include "Bullet.h"
class CPolygon;

class CBullet2 : public CBullet
{
public:
	CBullet2();
	void Draw() override;
	void Update(float deltatime) override;
	void SetPosition(float x, float y) override;

private:
	void CreateShape();
	CPolygon* m_shapeRectangle;
	float m_angleRotation;
};

