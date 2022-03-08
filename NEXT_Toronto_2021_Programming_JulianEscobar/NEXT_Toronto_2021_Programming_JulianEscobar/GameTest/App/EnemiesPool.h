#pragma once
//-----------------------------------------------------------------------------
// EnemiesPool.h
// Pool that contains all the enemies
//-----------------------------------------------------------------------------
#include "Enemy.h"
class CTurret;
class CEnemiesPool
{
public:
	static CEnemiesPool& getInstance()
	{
		static CEnemiesPool Instance;
		return Instance;
	}
	void AddEnemy1();
	void AddEnemy2();
	void AddEnemy3();

	void SpawnEnemy(std::vector<CEnemy*> pool);
	void SpawnEnemy1();
	void SpawnEnemy2();
	void SpawnEnemy3();

	void Draw();
	void Update(float deltatime);
	void UpdatePath();
	void Restart();

	CVertex getFirstEnemyInRange(CTurret* turret);
	CEnemy* getNextAvailable(std::vector<CEnemy*> pool);

	void UpgradeEnemies();
	std::vector<CEnemy*> getPool1() { return pool1; }
	std::vector<CEnemy*> getPool2() { return pool2; }
	std::vector<CEnemy*> getPool3() { return pool3; }

	void AddAnActiveEnemy() { m_numberOfActiveEnemies++; }
	void DeleteAnActiveEnemy() { m_numberOfActiveEnemies--; }
	int getNumberOfActiveEnemies() { return m_numberOfActiveEnemies; }

private:
	CEnemiesPool();
	float m_timer;
	int m_numberOfActiveEnemies;

	int m_numberEnemies = 20;
	std::vector<CEnemy*> pool1;
	std::vector<CEnemy*> pool2;
	std::vector<CEnemy*> pool3;
};