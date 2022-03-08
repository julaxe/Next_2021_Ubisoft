#pragma once
//-----------------------------------------------------------------------------
// Enemy3.h
// Creates an Enemy3
//-----------------------------------------------------------------------------
#include "Enemy.h"
class CPolygon;
class CEnemy3 : public CEnemy
{
public:
	CEnemy3(CNode* node);
	~CEnemy3();
	void Draw() override;
	void Update() override;
	void SetPosition(float x, float y) override;
	void SetColor(CColor color) override;
	void Reset() override;

private:
	void CreateShape();
	CPolygon* m_shapeTriangleFront;
	CPolygon* m_shapeTriangleBack;
};