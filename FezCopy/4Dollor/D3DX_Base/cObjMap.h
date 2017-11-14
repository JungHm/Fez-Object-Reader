#pragma once
#include "iMap.h"

class cObjMap : public iMap
{
private:
	std::vector<D3DXVECTOR3>	m_vecSurface;

public:
	cObjMap(char* szFolder, char* szFile, D3DXMATRIXA16* pMat = NULL);
	~cObjMap();

	void Load(char* szFolder, char* szFile, D3DXMATRIXA16* pMat = NULL);

	virtual bool GetHeight(IN float x, OUT float& y, IN float z) override;
};

