#pragma once
//-----------------------------------------------------------------------------
// Player.h
// Class that contains all the variables relevant to the player like health and score.
//-----------------------------------------------------------------------------
#include "Basics.h"
class CPolygon;
class CNode;

class Player
{
public:
	static Player& getInstance()
	{
		static Player Instance;
		return Instance;
	}
	void Draw();
	void Update(float deltatime);
	void Restart();

	void MoveNode(int dx, int dy);
	int getGridX() { return m_gridX; }
	int getGridY() { return m_gridY; }
	CNode* getCurrentNode() { return m_currentNode; }
	CColor getColor() { return yellow; }

	//game
	int getScore() { return m_score; }
	int getMoney() { return m_money; }
	int getHp() { return m_hp; }
	bool getGameOver() { return m_gameOver; }
	bool getPause() { return m_pause; }

	void setPause(bool pause) { m_pause = pause; }
	void setGameOver(bool gameover) { m_gameOver = gameover; }
	void takeScore(int score) { m_score += score; }
	void takeMoney(int money) { m_money += money; }
	void takeDamage(int damage) { m_hp += damage; }
	

private:
	//singleton
	Player();

	//shape
	void CreateShape();

	//game properties
	int m_score;
	int m_money;
	int m_hp;
	bool m_gameOver;
	bool m_pause;
	
	//selector properties
	CNode* m_currentNode;
	CPolygon* m_shapeSquare;
	CVertex m_position;
	int m_gridX;
	int m_gridY;

	//color selector
	CColor yellow;
};
