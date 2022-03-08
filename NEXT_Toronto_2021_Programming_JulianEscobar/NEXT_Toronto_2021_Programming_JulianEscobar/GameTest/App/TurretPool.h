#pragma once
//-----------------------------------------------------------------------------
// TurretPool.h
// pool for the Turrets
//-----------------------------------------------------------------------------
#include "Turret.h"
#include <vector>
class CTurretPool
{
public:
	static CTurretPool& getInstance()
	{
		static CTurretPool Instance;
		return Instance;
	}


	void PutTurret();
	void CombineTurrets();
	void SellSelectedTurrets();
	void Draw();
	void Update(float deltatime);
	void Restart();

private:
	//create the turret in the board
	void CreateTurret(std::vector<CTurret*> pool, CNode* node,  int cost);

	void AddTurret1();
	void AddTurret2();
	void AddTurret3();
	CTurret* checkIfTurretInNode(CNode* node);
	void selectTurret();
	void clearSelectedTurrets();
	
	CTurret* GetNextAvailableBullet(std::vector<CTurret*> pool);


	CTurretPool();
	int m_numberOfTurretsFirstPool = 80;

	std::vector<CTurret*> m_selectedTurrets;

	std::vector<CTurret*> pool1;
	std::vector<CTurret*> pool2;
	std::vector<CTurret*> pool3;
};
