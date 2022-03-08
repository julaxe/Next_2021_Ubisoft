#pragma once
//-----------------------------------------------------------------------------
// Turret3.h
// Creates Turret 3
//-----------------------------------------------------------------------------
#include "Turret.h"
class CNode;
class CPolygon;

class CTurret3 : public CTurret
{
public:
	CTurret3(CNode* node);
	~CTurret3();
	void Draw() override;
	void Update(float deltaTime) override;
	void SetPosition(float x, float y) override;
	void ChangeNode(CNode* node) override;
	void SetColor(CColor color) override;

private:
	void Shoot();
	void CreateShape();
	CPolygon* m_shapeRotatorySquare1;
	CPolygon* m_shapeRotatorySquare2;
	float m_angleRot1;
	float m_angleRot2;
	

	CPolygon* m_shapeTriangle;
	CPolygon* m_shapeMiniCircle;
};
