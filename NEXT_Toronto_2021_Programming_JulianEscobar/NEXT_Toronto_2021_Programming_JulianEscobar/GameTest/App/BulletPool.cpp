//-----------------------------------------------------------------------------
// BulletPool.cpp
// pool for the bullets
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "BulletPool.h"
//-----------------------------------------------------------------------------
#include "Bullet1.h"
#include "Bullet2.h"
#include "Bullet3.h"


void CBulletPool::Shoot1(CVertex position, CVertex direction)
{
	CBullet* bullet = GetNextAvailableBullet(pool1);
	if (bullet != nullptr) // there is available bullets
	{
		bullet->Activate(position, direction);
	}
}

void CBulletPool::Shoot2(CVertex position, CVertex direction)
{
	CBullet* bullet = GetNextAvailableBullet(pool2);
	if (bullet != nullptr) // there is available bullets
	{
		bullet->Activate(position, direction);
	}
}

void CBulletPool::Shoot3(CVertex position, CVertex direction)
{
	CBullet* bullet = GetNextAvailableBullet(pool3);
	if (bullet != nullptr) // there is available bullets
	{
		bullet->Activate(position, direction);
	}
}

void CBulletPool::Draw()
{
	for (auto bullet : pool1)
	{
		bullet->Draw();
	}
	for (auto bullet : pool2)
	{
		bullet->Draw();
	}
	for (auto bullet : pool3)
	{
		bullet->Draw();
	}
}

void CBulletPool::Update(float deltatime)
{
	for (auto bullet : pool1)
	{
		bullet->Update(deltatime);
	}
	for (auto bullet : pool2)
	{
		bullet->Update(deltatime);
	}
	for (auto bullet : pool3)
	{
		bullet->Update(deltatime);
	}
}

void CBulletPool::Restart()
{
	for (auto bullet : pool1)
	{
		if (bullet->isActive())
			bullet->Desactivate();
	}
	for (auto bullet : pool2)
	{
		if (bullet->isActive())
			bullet->Desactivate();
	}
	for (auto bullet : pool3)
	{
		if (bullet->isActive())
			bullet->Desactivate();
	}
}

void CBulletPool::AddBullet1()
{
	pool1.push_back(new CBullet1()); 
}

void CBulletPool::AddBullet2()
{
	pool2.push_back(new CBullet2());
}

void CBulletPool::AddBullet3()
{
	pool3.push_back(new CBullet3());
}


CBullet* CBulletPool::GetNextAvailableBullet(std::vector<CBullet*> pool)
{
	for (auto bullet : pool)
	{
		if (!bullet->isActive())
		{
			return bullet;
		}
	}

	return nullptr;
}

CBulletPool::CBulletPool()
{
	for (int i = 0; i < m_numberOfBulletsFirstPool; i++)
	{
		AddBullet1();
		AddBullet2();
		AddBullet3();
	}
}
