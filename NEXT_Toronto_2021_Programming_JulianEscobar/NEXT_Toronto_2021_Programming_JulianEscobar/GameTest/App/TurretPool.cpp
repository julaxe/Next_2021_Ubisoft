//-----------------------------------------------------------------------------
// BulletPool.cpp
// pool for the bullets
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "TurretPool.h"
//-----------------------------------------------------------------------------
#include "Turret1.h"
#include "Turret2.h"
#include "Turret3.h"
#include "Player.h"
#include "Board.h"
#include "EnemiesPool.h"
#include "UserInterface.h"

void CTurretPool::PutTurret()
{
	//first check if the node is available (turret or out of map)
	if (Player::getInstance().getCurrentNode()->isWalkable())
	{
		clearSelectedTurrets();
		//then check if the player has money
		CreateTurret(pool1, Player::getInstance().getCurrentNode(), 10);
	}
	else
	{
		//it can be a turret or out of the board
		//check if its a turret and if it is select it.
		selectTurret();
	}
}

void CTurretPool::CombineTurrets()
{
	//check if atleast 3 turrets are selected
	if (m_selectedTurrets.size() >= 3)
	{
		int level = m_selectedTurrets[0]->getLevel();
		for (auto turret : m_selectedTurrets)
		{
			if (level != turret->getLevel())
			{
				CUserInterface::getInstance().InfoMessage("Different Turrets! they need to be the same");
				return;
			}
		}
		//they are the same level now check the money
		if (level == 1)
		{
			if (Player::getInstance().getMoney() < 50)
			{
				CUserInterface::getInstance().InfoMessage("Not enough money to combine these turrets (50)");
				return;
			}
		}
		else if (level == 2)
		{
			if (Player::getInstance().getMoney() < 100)
			{
				CUserInterface::getInstance().InfoMessage("Not enough money to combine these turrets (100)");
				return;
			}
		}
		else if (level == 3)
		{
			CUserInterface::getInstance().InfoMessage("No Upgrade Available");
			return;
		}


		//we have money and they are selected properly, now lets combine
		//get the last 3, desactivate them, and then create the new one in the spot of the last one
		m_selectedTurrets[m_selectedTurrets.size() - 1]->Desactivate();
		m_selectedTurrets[m_selectedTurrets.size() - 2]->Desactivate();
		m_selectedTurrets[m_selectedTurrets.size() - 3]->Desactivate();
		if (level == 1)
		{
			CreateTurret(pool2, m_selectedTurrets[m_selectedTurrets.size() - 1]->getNode(), 50);
		}
		else if (level == 2)
		{
			CreateTurret(pool3, m_selectedTurrets[m_selectedTurrets.size() - 1]->getNode(), 100);
		}
		clearSelectedTurrets();
	}
	else
	{
		CUserInterface::getInstance().InfoMessage("You need atleast 3 turrets to combine");
	}
}

void CTurretPool::SellSelectedTurrets()
{
	if (m_selectedTurrets.size() > 0)
	{
		for (auto turret : m_selectedTurrets)
		{
			turret->SetColor(CColor()); // go back to white
			turret->Desactivate();
			Player::getInstance().takeMoney(turret->getCost());
		}
		m_selectedTurrets.clear();
	}
	else
	{
		CUserInterface::getInstance().InfoMessage("Nothing to sell");
	}
}

void CTurretPool::Draw()
{
	for (auto turret : pool1)
	{
		turret->Draw();
	}
	for (auto turret : pool2)
	{
		turret->Draw();
	}
	for (auto turret : pool3)
	{
		turret->Draw();
	}
}

void CTurretPool::Update(float deltatime)
{
	for (auto turret : pool1)
	{
		turret->Update(deltatime);
	}
	for (auto turret : pool2)
	{
		turret->Update(deltatime);
	}
	for (auto turret : pool3)
	{
		turret->Update(deltatime);
	}
}

void CTurretPool::Restart()
{
	for (auto turret : pool1)
	{
		if (turret->isActive())
			turret->Desactivate();
	}
	for (auto turret : pool2)
	{
		if (turret->isActive())
			turret->Desactivate();
	}
	for (auto turret : pool3)
	{
		if (turret->isActive())
			turret->Desactivate();
	}
}

void CTurretPool::CreateTurret(std::vector<CTurret*> pool, CNode* node, int cost)
{
	if (Player::getInstance().getMoney() >= cost)
	{
		//check if it doesn't close all paths
		node->setWalkability(false);
		CBoard::getInstance().Update();
		if (CBoard::getInstance().path.size() == 0)
		{
			//redo, is closing all paths.
			node->setWalkability(true);
			CBoard::getInstance().Update();
			CUserInterface::getInstance().InfoMessage("Can't close all possible paths!");
			return;
		}

		CTurret* turret = GetNextAvailableBullet(pool);

		//if everything is fine then put the turret on the board
		if (turret != nullptr)
		{
			turret->Activate(node);

			//that node is not walkable anymore because there is a turret there
			node->setWalkability(false);
			Player::getInstance().takeMoney(-cost);

			//update paths
			CBoard::getInstance().Update();
			CEnemiesPool::getInstance().UpdatePath();

		}
		return;
	}
	//message no money
	CUserInterface::getInstance().InfoMessage("Not enough money to buy turret (" + std::to_string(cost) + ")");
}


void CTurretPool::AddTurret1()
{
	pool1.push_back(new CTurret1(CBoard::getInstance().getFinishPoint()));
}

void CTurretPool::AddTurret2()
{
	pool2.push_back(new CTurret2(CBoard::getInstance().getFinishPoint()));
}

void CTurretPool::AddTurret3()
{
	pool3.push_back(new CTurret3(CBoard::getInstance().getFinishPoint()));
}

CTurret* CTurretPool::checkIfTurretInNode(CNode* node)
{
	for (auto turret : pool1)
	{
		if (turret->getNode() == node)
		{
			if(turret->isActive())
				return turret;
		}
	}
	for (auto turret : pool2)
	{
		if (turret->getNode() == node)
		{
			if (turret->isActive())
				return turret;
		}
	}
	for (auto turret : pool3)
	{
		if (turret->getNode() == node)
		{
			if (turret->isActive())
				return turret;
		}
	}
	return nullptr;
}

void CTurretPool::selectTurret()
{
	CTurret* selectedTurret = checkIfTurretInNode(Player::getInstance().getCurrentNode());
	if (selectedTurret != nullptr)
	{
		if (selectedTurret->getColor() == Player::getInstance().getColor())
		{
			//is already selected - do nothing
			return;
		}
		selectedTurret->SetColor(Player::getInstance().getColor());
		m_selectedTurrets.push_back(selectedTurret);
	}
	else
	{
		clearSelectedTurrets();
	}
}

void CTurretPool::clearSelectedTurrets()
{
	for (auto turret : m_selectedTurrets)
	{
		turret->SetColor(CColor()); // go back to white
	}
	m_selectedTurrets.clear();
}



CTurret* CTurretPool::GetNextAvailableBullet(std::vector<CTurret*> pool)
{
	for (auto turret : pool)
	{
		if (!turret->isActive())
		{
			return turret;
		}
	}

	return nullptr;
}

CTurretPool::CTurretPool()
{
	for (int i = 0; i < m_numberOfTurretsFirstPool; i++)
	{
		AddTurret1();
		AddTurret2();
		AddTurret3();
	}
}
