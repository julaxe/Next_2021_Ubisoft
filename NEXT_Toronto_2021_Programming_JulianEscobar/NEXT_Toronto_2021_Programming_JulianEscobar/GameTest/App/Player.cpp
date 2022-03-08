//-----------------------------------------------------------------------------
// Player.cpp
// Class that contains all the variables relevant to the player like health and score.
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include "Player.h"
#include "Polygon.h"
#include "app.h"
#include "Board.h"
#include "Node.h"
void Player::Draw()
{
	m_shapeSquare->Draw();
}

void Player::Update(float deltatime)
{
	if (m_hp <= 0)
	{
		m_gameOver = true;
	}
}

void Player::Restart()
{
	m_score = 0;
	m_money = 100;
	m_hp = 50;
	m_gameOver = false;
}

void Player::MoveNode(int dx, int dy)
{
	m_gridX += dx;
	m_gridY += dy;
	if (m_gridX > COLS-1)
	{
		m_gridX = COLS-1;
	}
	if (m_gridX < 0)
	{
		m_gridX = 0;
	}
	if (m_gridY > ROWS-1)
	{
		m_gridY = ROWS-1;
	}
	if (m_gridY < 0)
	{
		m_gridY = 0;
	}

	m_currentNode = CBoard::getInstance().grid[m_gridY][m_gridX];
	m_position = *m_currentNode->getPosition();
	m_shapeSquare->SetPosition(m_position.x, m_position.y);

}

void Player::CreateShape()
{
	m_shapeSquare = new CPolygon(4, 32.f, yellow);
	m_currentNode = CBoard::getInstance().grid[m_gridY][m_gridX];
	m_position = *m_currentNode->getPosition();
	m_shapeSquare->SetPosition(m_position.x, m_position.y);
}
Player::Player()
{
	//game properties
	m_score = 0;
	m_money = 100;
	m_hp = 50;
	m_gameOver = false;

	m_gridX = (COLS-1)/2;
	m_gridY = (ROWS-1)/2;
	yellow = CColor(1.0f, 1.0f, 0.1f);
	CreateShape();
}
