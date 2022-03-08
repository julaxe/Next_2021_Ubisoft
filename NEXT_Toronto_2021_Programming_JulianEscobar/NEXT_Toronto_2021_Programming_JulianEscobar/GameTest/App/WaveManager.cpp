//-----------------------------------------------------------------------------
// WaveManager.cpp
// Utility function for controlling waves spawning
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "WaveManager.h"
//-----------------------------------------------------------------------------
#include "EnemiesPool.h"
#include "UserInterface.h"
#include "MathManager.h"

void CWaveManager::Update(float deltatime)
{
	//check if is in between waves
	if (m_break)
	{
		//if its in break update the message
		if (m_timer < m_waitTime)
		{
			m_countDown = m_waitTime - (int)m_timer;
			CUserInterface::getInstance().InfoMessage2("Next wave in: " + std::to_string(m_countDown));
		}
		else
		{
			m_timer = 0.0f;
			m_break = false;
			CUserInterface::getInstance().DefaultMessage2();
		}
	}
	else
	{
		//spawn waves
		SpawnWave();

		if (m_doneSpawning)
		{
			if (CEnemiesPool::getInstance().getNumberOfActiveEnemies() <= 0)
			{
				InitCountDown(5); //next wave in 5 seconds
			}
		}
		
	}
	m_timer += deltatime / 1000.f;

}

void CWaveManager::InitCountDown(int waitTime)
{
	m_break = true;
	m_waitTime = waitTime;
	m_timer = 0.0f;
	m_waveNumber++;
	m_numberEnemiesWave += 5;
	if (m_numberEnemiesWave > 20)
	{
		m_numberEnemiesWave = 5;
		CEnemiesPool::getInstance().UpgradeEnemies();
	}
	m_enemiesSpawned = 0;
	m_doneSpawning = false;
}

void CWaveManager::SpawnWave()
{
	if (m_enemiesSpawned < m_numberEnemiesWave)
	{
		if (m_timer > 0.5f) //delay between enemies spawn
		{
			int randomNumber = MathManager::RandInt(1, 10);
			//spawn enemy 1
			if (randomNumber < 7)
			{
				CEnemiesPool::getInstance().SpawnEnemy1();
			}
			//spawn enemy 2
			else if (randomNumber >= 7 && randomNumber <= 8)
			{
				CEnemiesPool::getInstance().SpawnEnemy2();
			}
			else
			{
				CEnemiesPool::getInstance().SpawnEnemy3();
			}

			//spawn enemy 3

			m_enemiesSpawned++;
			m_timer = 0.0f;
		}
	}
	else
	{
		m_doneSpawning = true;
	}
}

void CWaveManager::Restart()
{
	m_enemiesSpawned = 0;
	m_numberEnemiesWave = 0;
	m_break = false;
	m_doneSpawning = false;
	m_countDown = 0;
	m_timer = 0.0;
	m_waveNumber = 0;
}


CWaveManager::CWaveManager()
{
	Restart();
}
