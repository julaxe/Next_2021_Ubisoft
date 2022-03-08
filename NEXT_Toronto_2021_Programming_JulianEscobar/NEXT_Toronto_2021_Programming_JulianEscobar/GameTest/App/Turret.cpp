//-----------------------------------------------------------------------------
// Turret.cpp
// Creates a Turret
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include "Turret.h"
#include "Node.h"

CTurret::CTurret(CNode* node)
{
	m_level = 0;
	m_node = node;
	m_active = false;
	m_fireRate = 1.0f;
	m_color = new CColor();
	m_angle = 0.0f;
	m_front = new CVertex(cosf(m_angle), sinf(m_angle));
}

CTurret::~CTurret()
{
	delete m_color;
	delete m_front;
}

void CTurret::Aim(CVertex enemyPos)
{
	CVertex delta = enemyPos - *m_node->getPosition();
	m_angle = atan2f(delta.y, delta.x);
	*m_front = CVertex(cosf(m_angle), sinf(m_angle));
}


void CTurret::Desactivate()
{
	m_active = false;
	m_node->setWalkability(true);
}

void CTurret::Activate(CNode* node)
{
	m_node = node;
	SetPosition(m_node->getPosition()->x, m_node->getPosition()->y);
	m_active = true;
	*m_color = CColor();
}

