//-----------------------------------------------------------------------------
// Enemy.cpp
// Creates an enemy
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include "Enemy.h"
#include "Node.h"
#include "PathFindingManager.h"
#include "Board.h"
#include "EnemiesPool.h"
#include "Player.h"
#include "app.h"

CEnemy::CEnemy(CNode* node)
{
	m_currentNode = node;
	m_path = PathFindingManager::FindPath(m_currentNode, CBoard::getInstance().getFinishPoint());
	m_colorUpgrade = CColor();
	m_active = false;
	GoToNextNode();
	m_speed = 0;
	m_radius = 0;
}

CEnemy::~CEnemy()
{
}

void CEnemy::UpdatePath()
{
	m_path = PathFindingManager::FindPath(m_currentNode, CBoard::getInstance().getFinishPoint());
	GoToNextNode();
}

void CEnemy::FollowPath()
{
	if (m_active)
	{
		CVertex delta = *m_nextNode->getPosition() - m_position;
		if(delta.Magnitude() != 0.0f)
			Move(delta);

		if (delta.Magnitude() < 1.0f)
		{
			m_currentNode = m_nextNode;
			GoToNextNode();
		}
	}
}

bool CEnemy::GoToNextNode()
{
	if (m_path.size() > 0)
	{
		m_nextNode = m_path.back();
		m_path.pop_back();
		Rotate(GetangleToNextNode());
		return true;
	}
	Player::getInstance().takeDamage(-10);
	Desactivate();
	return false;
}

void CEnemy::Move(CVertex dp)
{
	CVertex direction = dp.ConvertToUnit();
	CVertex velocity = direction * m_speed;
	m_position = m_position + velocity;
	SetPosition(m_position.x, m_position.y);
}

void CEnemy::Rotate(float angle)
{
	m_angle = angle;
}

void CEnemy::IncreaseMaxHp(float times)
{
	m_hp *= times;
}

float CEnemy::GetangleToNextNode()
{
	CVertex delta = *m_nextNode->getPosition() - m_position;
	float newAngle = atan2f(delta.y, delta.x);
	return newAngle;
}

void CEnemy::TakeDamage(float damage)
{
	m_currentHp -= damage;
	App::PlaySound(".\\TestData\\hit.wav");
	if (m_currentHp <= 0)
	{
		Desactivate();
		return;
	}
	float Redish = (m_hp - m_currentHp) / m_hp;
	CColor newColor = CColor(1.0f, 1.0f - Redish, 1.0f - Redish);
	SetColor(newColor);
}

void CEnemy::Desactivate()
{
	m_active = false;
	CEnemiesPool::getInstance().DeleteAnActiveEnemy();
	Player::getInstance().takeMoney(10);
	Player::getInstance().takeScore(5);
	//give Score to player and money
}

void CEnemy::Activate(CNode* node)
{
	//reset hp
	m_currentHp = m_hp;

	//Reset position
	m_currentNode = node;
	SetPosition(m_currentNode->getPosition()->x, m_currentNode->getPosition()->y);

	//reset color
	SetColor(m_colorUpgrade);

	//reset path
	m_path = PathFindingManager::FindPath(m_currentNode, CBoard::getInstance().getFinishPoint());
	GoToNextNode();

	//set active
	m_active = true;
	CEnemiesPool::getInstance().AddAnActiveEnemy();
}
