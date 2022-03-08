#pragma once
//-----------------------------------------------------------------------------
// Enemy2.h
// Creates an Enemy2
//-----------------------------------------------------------------------------
#include "Enemy.h"
class CPolygon;
class CEnemy2 : public CEnemy
{
public:
	CEnemy2(CNode* node);
	~CEnemy2();
	void Draw() override;
	void Update() override;
	void SetPosition(float x, float y) override;
	void SetColor(CColor color) override;
	void Reset() override;

	void SetWheel(CPolygon* wheel, float offSetAngle);


private:
	void CreateShape();
	CPolygon* m_shapeBiCircle;
	CPolygon* m_shapeWheel1;
	CPolygon* m_shapeWheel2;
	CPolygon* m_shapeWheel3;
	CPolygon* m_shapeWheel4;
};
