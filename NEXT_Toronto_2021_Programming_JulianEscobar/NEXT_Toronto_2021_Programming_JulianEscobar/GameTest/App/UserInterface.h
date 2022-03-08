#pragma once
//-----------------------------------------------------------------------------
// UserInterface.h
// Creates the User interface where the User can see the actual stats of the game
//-----------------------------------------------------------------------------
#include <string>
class CUserInterface
{
public:
	static CUserInterface& getInstance()
	{
		static CUserInterface Instance;
		return Instance;
	}
	void Draw();
	void Update(float deltatime);
	void InfoMessage(std::string info);
	void InfoMessage2(std::string info);
	void DefaultMessage();
	void DefaultMessage2();
private:
	CUserInterface();

	float m_timer;
	float m_timer2;
	std::string m_moneyStatus;
	std::string m_hpStatus;
	std::string m_enemiesStatus;
	std::string m_waveStatus;
	std::string m_scoreStatus;
	std::string m_message;
	std::string m_message2;

};