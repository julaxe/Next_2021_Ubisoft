#pragma once
//-----------------------------------------------------------------------------
// Enemy1.h
// Creates an Enemy1
//-----------------------------------------------------------------------------
#include "Enemy.h"
class CPolygon;
class CEnemy1 : public CEnemy
{
public:
	CEnemy1(CNode* node);
	~CEnemy1();
	void Draw() override;
	void Update() override;
	void SetPosition(float x, float y) override;
	void SetColor(CColor color) override;
	void Reset() override;


private:
	void CreateShape();
	CPolygon* m_shapeCircle1;
	CPolygon* m_shapeCircle2;
};