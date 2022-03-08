//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------
#include <time.h>

CBoard* board;

void Init()
{
	srand((unsigned int)time(NULL));

	// wait 15 seconds at the start of the game
	CWaveManager::getInstance().InitCountDown(15);
	CUserInterface::getInstance().InfoMessage("Welcome To Tower Defense");

	App::PlaySound(".\\TestData\\background_music.wav", true);
}

void Update(float deltaTime)
{
	if (!Player::getInstance().getGameOver() && !Player::getInstance().getPause())
	{
		CWaveManager::getInstance().Update(deltaTime);
		CEnemiesPool::getInstance().Update(deltaTime);
		CBulletPool::getInstance().Update(deltaTime);
		CTurretPool::getInstance().Update(deltaTime);
		CUserInterface::getInstance().Update(deltaTime);
		Player::getInstance().Update(deltaTime);
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
		{
			CTurretPool::getInstance().PutTurret();
		}
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
		{
			CTurretPool::getInstance().CombineTurrets();
		}
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_Y, true))
		{
			CTurretPool::getInstance().SellSelectedTurrets();
		}
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
		{
			Player::getInstance().setPause(true);
		}
	}
	else
	{
		if (Player::getInstance().getGameOver())
		{
			CUserInterface::getInstance().InfoMessage("Press 'Space' to Start Again");
			if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
			{
				CWaveManager::getInstance().Restart();
				CTurretPool::getInstance().Restart();
				CBulletPool::getInstance().Restart();
				CEnemiesPool::getInstance().Restart();
				Player::getInstance().Restart();
			}
		}
		else // is just paused
		{
			CUserInterface::getInstance().InfoMessage("Press 'P' to UnPause");
			if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
			{
				Player::getInstance().setPause(false);
			}
		}
	}

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, true))
	{
		Player::getInstance().MoveNode(0, 1);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, true))
	{
		Player::getInstance().MoveNode(0, -1);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, true))
	{
		Player::getInstance().MoveNode(-1, 0);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, true))
	{
		Player::getInstance().MoveNode(1, 0);
	}
}

void Render()
{	
	CBoard::getInstance().Draw();
	
	CEnemiesPool::getInstance().Draw();
	CBulletPool::getInstance().Draw();
	CTurretPool::getInstance().Draw();
	Player::getInstance().Draw();
	CUserInterface::getInstance().Draw();

	//UI
	

}

void Shutdown()
{	
	
}