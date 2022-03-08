///////////////////////////////////////////////////////////////////////////////
// Filename: Node.cpp
// Node that allow to know the possible paths for the enemy and where to put towers.
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include "Node.h"
#include "Basics.h"
#include "DebugManager.h"

CNode::CNode(float x, float y, int gridX, int gridY)
{
	m_position = new CVertex(x, y);
	m_color = new CColor(0.2f, 0.2f, 0.2f);
	m_collisionBox = new CRect(x, y, NODE_SIZE, NODE_SIZE);
	m_walkable = true;
	this->gridX = gridX;
	this->gridY = gridY;
	this->parent = nullptr;
}

CNode::~CNode()
{
	delete m_position;
	delete m_color;
	delete m_collisionBox;
	delete parent;
}

void CNode::DrawNode()
{
	CRect center = CRect(m_collisionBox->x, m_collisionBox->y, 1, 1);
	if (m_walkable)
	{
		DebugManager::DrawRect(*m_collisionBox, *m_color);
		DebugManager::DrawRect(center, *m_color);
	}
	else
	{
		//DebugManager::DrawRect(*m_collisionBox, {1.0f,0.0f,0.0f}); // red
		//DebugManager::DrawRect(center, {1.0f,0.0f,0.0f}); // red
	}
}

bool CNode::operator>(CNode  &b)
{
	if (this->getFCost() > b.getFCost()) //less f cost -> more priority.
	{
		return true;
	}
	return false;
}

bool CNode::operator<(CNode &b)
{
	if (this->getFCost() < b.getFCost())
	{
		return true;
	}
	return false;
}
