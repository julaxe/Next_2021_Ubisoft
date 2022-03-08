#pragma once
//-----------------------------------------------------------------------------
// Turret.h
// Creates a Turret
//-----------------------------------------------------------------------------
class CNode;
#include "Basics.h"
class CTurret
{
public:
	CTurret(CNode* node);
	~CTurret();
	virtual void Draw() {};
	virtual void Update(float deltaTime) {};
	virtual void SetPosition(float x, float y) {};
	virtual void ChangeNode(CNode* node) {};
	virtual void SetColor(CColor color) {}

	int getCost() { return m_cost; }
	float getRange() { return m_range; }
	void Aim(CVertex enemyPos);
	CNode* getNode() { return m_node; }
	CColor getColor() { return *m_color; }
	int getLevel() { return m_level; }

	bool isActive() { return m_active; }
	void Desactivate();
	void Activate(CNode* node);

protected:

	int m_cost;
	int m_level;
	float m_timer;
	float m_range;
	float m_angle;
	CVertex* m_front;
	float m_fireRate;
	bool m_active;
	CNode* m_node;
	CColor* m_color;
	
};