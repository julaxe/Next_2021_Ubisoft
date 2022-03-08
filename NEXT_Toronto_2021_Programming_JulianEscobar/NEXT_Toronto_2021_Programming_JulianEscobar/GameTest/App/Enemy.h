#pragma once
//-----------------------------------------------------------------------------
// Enemy.h
// Creates an Enemy
//-----------------------------------------------------------------------------
#include <vector>
#include "Basics.h"
class CNode;
class CEnemy
{
public:
	CEnemy(CNode* node);
	~CEnemy();
	virtual void Draw() {}
	virtual void Update() {}
	virtual void SetPosition(float x, float y) {}
	virtual void SetColor(CColor color) {}
	virtual void Reset() {}
	CColor getColor() { return m_color; }
	CColor getColorUpgrade() { return m_colorUpgrade; }
	void setColorUpgrade(CColor color) { m_colorUpgrade = color; }
	CVertex getPosition() { return m_position; }
	float getRadius() { return m_radius; }
	void UpdatePath();
	void FollowPath();
	bool GoToNextNode();
	void Move(CVertex dp);
	void Rotate(float angle);

	
	void IncreaseMaxHp(float times);
	float GetangleToNextNode();
	void TakeDamage(float damage);

	bool isActive() { return m_active; }
	void Desactivate();
	void Activate(CNode* node);

protected:

	float m_hp;
	float m_currentHp;
	CColor m_color;
	CColor m_colorUpgrade;

	float m_radius;
	float m_angle;

	bool m_active;

	float m_speed;
	CVertex m_position;
	CNode* m_nextNode;
	CNode* m_currentNode;
	std::vector<CNode*> m_path;

	
};