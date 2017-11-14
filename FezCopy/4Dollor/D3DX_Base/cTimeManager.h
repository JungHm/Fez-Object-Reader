#pragma once
#define g_pTimeManager	cTimeManager::GetInstance()

class cTimeManager
{
private:
	SINGLETONE(cTimeManager);

	DWORD m_dwLastUpdateTime;
	float m_fEllapsedTime;

public:
	void Update();
	float GetLastUpdateTime();
	float GetEllapsedTime();
};

