#pragma once
//-----------------------------------------------------------------------------
// WaveManager.h
// Utility function for controlling waves spawning
//-----------------------------------------------------------------------------

class CWaveManager
{
public:
	static CWaveManager& getInstance()
	{
		static CWaveManager Instance;
		return Instance;
	}
	void Update(float deltatime);
	void InitCountDown(int waitTime);
	void SpawnWave();
	void Restart();
	
	int getCountDown() { return m_countDown; }
	int getWaveNumber() { return m_waveNumber; }

private:
	
	int m_enemiesSpawned;
	int m_numberEnemiesWave;
	bool m_break;
	bool m_doneSpawning;
	float m_timer;

	int m_countDown;
	int m_waitTime;
	int m_waveNumber;
	CWaveManager();
};
