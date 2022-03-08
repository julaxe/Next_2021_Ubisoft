//-----------------------------------------------------------------------------
// UserInterface.h
// Creates the User interface where the User can see the actual stats of the game
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "UserInterface.h"
//-----------------------------------------------------------------------------
#include "app.h"
#include "Player.h"
#include "EnemiesPool.h"


void CUserInterface::Draw()
{
	App::Print(APP_VIRTUAL_WIDTH * 0.05f, APP_VIRTUAL_HEIGHT - 30.f, m_enemiesStatus.c_str());
	App::Print(APP_VIRTUAL_WIDTH * 0.25f, APP_VIRTUAL_HEIGHT - 30.f, m_moneyStatus.c_str());
	App::Print(APP_VIRTUAL_WIDTH * 0.45f, APP_VIRTUAL_HEIGHT - 30.f, m_waveStatus.c_str());
	App::Print(APP_VIRTUAL_WIDTH * 0.65f, APP_VIRTUAL_HEIGHT - 30.f, m_hpStatus.c_str());
	App::Print(APP_VIRTUAL_WIDTH * 0.85f, APP_VIRTUAL_HEIGHT - 30.f, m_scoreStatus.c_str());

	App::Print(10.f, 20.f, "CONTROLS:");
	App::Print(APP_VIRTUAL_WIDTH * 0.2f, 30.f, "Arrows -> Move", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_12);
	App::Print(APP_VIRTUAL_WIDTH * 0.2f, 15.f, "Space  -> Select/Buy Turret", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_12);
	App::Print(APP_VIRTUAL_WIDTH * 0.4f, 30.f, "Z  -> Sell Turrets     P  -> Pause/UnPause", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_12);
	App::Print(APP_VIRTUAL_WIDTH * 0.4f, 15.f, "C  -> Combine Turrets (3 of the same type)", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_12);

	App::Print(APP_VIRTUAL_WIDTH * 0.7f, 20.f, "INFO:");
	App::Print(APP_VIRTUAL_WIDTH * 0.76f, 35.f, m_message.c_str(), 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_12);
	App::Print(APP_VIRTUAL_WIDTH * 0.76f, 23.f, m_message2.c_str(), 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_12);
}

void CUserInterface::Update(float deltatime)
{
	m_enemiesStatus = "ENEMIES: " + std::to_string(CEnemiesPool::getInstance().getNumberOfActiveEnemies());
	m_moneyStatus = "MONEY: " + std::to_string(Player::getInstance().getMoney());
	m_waveStatus = "WAVE: " + std::to_string(CWaveManager::getInstance().getWaveNumber());
	m_hpStatus = "HP: " + std::to_string(Player::getInstance().getHp());
	m_scoreStatus = "SCORE: " + std::to_string(Player::getInstance().getScore());

	//show the message and then go back to default message
	if (m_timer > 3.0f)
	{
		DefaultMessage();
	}
	if (m_timer2 > 3.0)
	{
		DefaultMessage2();
	}
	m_timer += deltatime / 1000.f;
	m_timer2 += deltatime / 1000.f;
}

void CUserInterface::InfoMessage(std::string info)
{
	m_message = info;
	m_timer = 0.0f;
}

void CUserInterface::InfoMessage2(std::string info)
{
	m_message2 = info;
	m_timer2 = 0.0f;
}

void CUserInterface::DefaultMessage()
{
	m_message = "Tower Defense for Ubisoft NEXT";
}

void CUserInterface::DefaultMessage2()
{
	m_message2 = "Enjoy!";
}

CUserInterface::CUserInterface()
{
	m_timer = 0;
	m_enemiesStatus = "";
	m_moneyStatus = "";
	m_hpStatus = "";
	m_scoreStatus = "";
	m_waveStatus = "";
	m_message = "Tower Defense by Julian Escobar";
	m_message2 = "Enjoy!";
}