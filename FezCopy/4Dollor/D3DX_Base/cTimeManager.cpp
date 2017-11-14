#include "stdafx.h"
#include "cTimeManager.h"


cTimeManager::cTimeManager()
{
	m_dwLastUpdateTime = GetTickCount();
}


cTimeManager::~cTimeManager()
{
}

void cTimeManager::Update()
{
	DWORD dwCurrTime = GetTickCount();
	m_fEllapsedTime = (dwCurrTime - m_dwLastUpdateTime) / 1000.0f;
	m_dwLastUpdateTime = dwCurrTime;
}

float cTimeManager::GetLastUpdateTime()
{
	return m_dwLastUpdateTime / 1000.0f;
}

float cTimeManager::GetEllapsedTime()
{
	return m_fEllapsedTime;
}
