//-----------------------------------------------------------------------------
// EnemiesPool.cpp
// Pool that contains all the enemies
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "EnemiesPool.h"
//-----------------------------------------------------------------------------
#include "Enemy1.h"
#include <algorithm>
#include "Board.h"
#include "Turret.h"
#include "Enemy2.h"
#include "Enemy3.h"

void CEnemiesPool::AddEnemy1()
{
	pool1.push_back(new CEnemy1(CBoard::getInstance().getStartPoint()));
}

void CEnemiesPool::AddEnemy2()
{
	pool2.push_back(new CEnemy2(CBoard::getInstance().getStartPoint()));
}

void CEnemiesPool::AddEnemy3()
{
	pool3.push_back(new CEnemy3(CBoard::getInstance().getStartPoint()));
}

void CEnemiesPool::SpawnEnemy(std::vector<CEnemy*> pool)
{
	CEnemy* enemy = getNextAvailable(pool);
	if (enemy != nullptr)
	{
		enemy->Activate(CBoard::getInstance().getStartPoint());
	}
}

void CEnemiesPool::SpawnEnemy1()
{
	SpawnEnemy(pool1);
}

void CEnemiesPool::SpawnEnemy2()
{
	SpawnEnemy(pool2);
}

void CEnemiesPool::SpawnEnemy3()
{
	SpawnEnemy(pool3);
}


void CEnemiesPool::Draw()
{
	for (auto enemy : pool1)
	{
		enemy->Draw();
	}
	for (auto enemy : pool2)
	{
		enemy->Draw();
	}
	for (auto enemy : pool3)
	{
		enemy->Draw();
	}
}

void CEnemiesPool::Update(float deltatime)
{
	
	for (auto enemy : pool1)
	{
		enemy->Update();
	}
	for (auto enemy : pool2)
	{
		enemy->Update();
	}
	for (auto enemy : pool3)
	{
		enemy->Update();
	}
}

void CEnemiesPool::UpdatePath()
{
	for (auto enemy : pool1)
	{
		if (enemy->isActive())
		{
			enemy->UpdatePath();
		}
	}
	for (auto enemy : pool2)
	{
		if (enemy->isActive())
		{
			enemy->UpdatePath();
		}
	}
	for (auto enemy : pool3)
	{
		if (enemy->isActive())
		{
			enemy->UpdatePath();
		}
	}
}

void CEnemiesPool::Restart()
{
	for (auto enemy : pool1)
	{
		enemy->Reset();
		if(enemy->isActive())
			enemy->Desactivate();
	}
	for (auto enemy : pool2)
	{
		enemy->Reset();
		if (enemy->isActive())
			enemy->Desactivate();
	}
	for (auto enemy : pool3)
	{
		enemy->Reset();
		if (enemy->isActive())
			enemy->Desactivate();
	}
}

CVertex CEnemiesPool::getFirstEnemyInRange(CTurret* turret)
{
	//check first for strongest enemies
	for (auto enemy : pool3)
	{
		if (enemy->isActive())
		{
			CVertex distance = enemy->getPosition() - *turret->getNode()->getPosition();
			float d = distance.Magnitude();
			if (d < turret->getRange())
			{
				return enemy->getPosition();
			}
		}
	}
	for (auto enemy : pool2)
	{
		if (enemy->isActive())
		{
			CVertex distance = enemy->getPosition() - *turret->getNode()->getPosition();
			float d = distance.Magnitude();
			if (d < turret->getRange())
			{
				return enemy->getPosition();
			}
		}
	}
	for (auto enemy : pool1)
	{
		if (enemy->isActive())
		{
			CVertex distance = enemy->getPosition() - *turret->getNode()->getPosition();
			float d = distance.Magnitude();
			if (d < turret->getRange())
			{
				return enemy->getPosition();
			}
		}
	}
	return CVertex(0.0f, 0.0f);;
}

CEnemy* CEnemiesPool::getNextAvailable(std::vector<CEnemy*> pool)
{
	for (auto enemy : pool)
	{
		if (!enemy->isActive())
		{
			return enemy;
		}
	}
	return nullptr;
}

void CEnemiesPool::UpgradeEnemies()
{
	for (auto enemy : pool1)
	{
		enemy->IncreaseMaxHp(2.0f);
		enemy->setColorUpgrade({ enemy->getColorUpgrade().r - 0.2f,enemy->getColorUpgrade().g - 0.2f, 1.0f });
	}
	for (auto enemy : pool2)
	{
		enemy->IncreaseMaxHp(2.0f);
		enemy->setColorUpgrade({ enemy->getColorUpgrade().r - 0.2f,enemy->getColorUpgrade().g - 0.2f, 1.0f });
	}
	for (auto enemy : pool3)
	{
		enemy->IncreaseMaxHp(2.0f);
		enemy->setColorUpgrade({ enemy->getColorUpgrade().r - 0.2f,enemy->getColorUpgrade().g - 0.2f, 1.0f });
	}

}

CEnemiesPool::CEnemiesPool()
{
	for (int i = 0; i < m_numberEnemies; i++)
	{
		AddEnemy1();
		AddEnemy2();
		AddEnemy3();
	}

	CBoard::getInstance().Update();
}
