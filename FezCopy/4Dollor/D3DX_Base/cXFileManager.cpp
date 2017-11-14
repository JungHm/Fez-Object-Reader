#include "stdafx.h"
#include "cXFileManager.h"


cXFileManager::cXFileManager()
{
}


cXFileManager::~cXFileManager()
{
}

void cXFileManager::Destroy()
{
	for each(auto p in m_pXFile)
	{
		p.second->Destroy();
		SAFE_DELETE(p.second);
	}
	m_pXFile.clear();
}
