#pragma once
#include "cXLoader.h"

#define XFile cXFileManager::GetInstance()

class cXFileManager
{
private:
	std::map<int, cXLoader*> m_pXFile;
public:
	SINGLETONE(cXFileManager);

	cXLoader* GetXFile(int key) { return m_pXFile[key]; }
	void SetXFile(int key, std::wstring path) {
		m_pXFile[key] = new cXLoader;
		m_pXFile[key]->XfileLoad(path);
	}
	LPD3DXANIMATIONCONTROLLER GetAniCtrl(int key) { return m_pXFile[key]->getAnimCtrl(); }

	void Destroy();
};

