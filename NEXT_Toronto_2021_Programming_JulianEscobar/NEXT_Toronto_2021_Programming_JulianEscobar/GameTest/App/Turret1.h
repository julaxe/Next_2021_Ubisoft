#pragma once
//-----------------------------------------------------------------------------
// Turret1.h
// Creates Turret 1
//-----------------------------------------------------------------------------
#include "Turret.h"
class CNode;
class CPolygon;

class CTurret1 : public CTurret
{
public:
	CTurret1(CNode* node);
	~CTurret1();
	void Draw() override;
	void Update(float deltaTime) override;
	void SetPosition(float x, float y) override;
	void ChangeNode(CNode* node) override;
	void SetColor(CColor color) override;

private:
	void Shoot();
	void CreateShape();
	CPolygon* m_shapeCircle;
	CPolygon* m_shapeTriangle;
	CPolygon* m_shapeMiniCircle;
};