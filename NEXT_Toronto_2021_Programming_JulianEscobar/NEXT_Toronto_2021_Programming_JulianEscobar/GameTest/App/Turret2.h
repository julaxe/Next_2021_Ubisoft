#pragma once
//-----------------------------------------------------------------------------
// Turret2.h
// Creates Turret 2
//-----------------------------------------------------------------------------
#include "Turret.h"
class CNode;
class CPolygon;

class CTurret2 : public CTurret
{
public:
	CTurret2(CNode* node);
	~CTurret2();
	void Draw() override;
	void Update(float deltaTime) override;
	void SetPosition(float x, float y) override;
	void ChangeNode(CNode* node) override;
	void SetColor(CColor color) override;

private:
	void Shoot();
	void CreateShape();
	CPolygon* m_shapeSquare;
	CPolygon* m_shapeRotatorySquare;
	float m_angleRot;

	CPolygon* m_shapeTriangle;
	CPolygon* m_shapeMiniCircle;
};
