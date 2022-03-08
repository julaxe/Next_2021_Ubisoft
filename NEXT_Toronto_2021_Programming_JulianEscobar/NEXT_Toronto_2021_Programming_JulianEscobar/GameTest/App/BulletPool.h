#pragma once
//-----------------------------------------------------------------------------
// BulletPool.h
// pool for the bullets
//-----------------------------------------------------------------------------
#include "Bullet.h"
#include <vector>
class CBulletPool
{
public:
	static CBulletPool& getInstance()
	{
		static CBulletPool Instance;
		return Instance;
	}

	void Shoot1(CVertex position, CVertex direction);
	void Shoot2(CVertex position, CVertex direction);
	void Shoot3(CVertex position, CVertex direction);
	void Draw();
	void Update(float deltatime);
	void Restart();
	
private:

	int m_numberOfBulletsFirstPool = 50;
	void AddBullet1();
	void AddBullet2();
	void AddBullet3();
	CBullet* GetNextAvailableBullet(std::vector<CBullet*> pool);
	CBulletPool();
	std::vector<CBullet*> pool1;
	std::vector<CBullet*> pool2;
	std::vector<CBullet*> pool3;
};