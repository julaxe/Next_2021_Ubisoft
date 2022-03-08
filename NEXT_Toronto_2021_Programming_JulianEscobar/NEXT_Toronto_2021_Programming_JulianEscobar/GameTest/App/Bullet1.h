#pragma once
//-----------------------------------------------------------------------------
// Bullet1.h
// first type of bullets
//-----------------------------------------------------------------------------
#include "Bullet.h"
class CPolygon;

class CBullet1 : public CBullet
{
public:
	CBullet1();
	void Draw() override;
	void Update(float deltatime) override;
	void SetPosition(float x, float y) override;

private:
	void CreateShape();
	CPolygon* m_shapeRectangle;
};
