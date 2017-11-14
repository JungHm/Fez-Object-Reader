#include "stdafx.h"
#include "cTextureManager.h"


cTextureManager::cTextureManager()
{
}


cTextureManager::~cTextureManager()
{
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(std::string sFullPath)
{
	char* szbuf = "fefefefef";
	std::string s(szbuf, szbuf + strlen(szbuf));
	std::wstring ws(sFullPath.begin(), sFullPath.end());
	if (m_mapTexture.find(sFullPath) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFile(g_pD3DDevice,
			ws.c_str(),
			&m_mapTexture[sFullPath]);
	}
	return m_mapTexture[sFullPath];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(char * szFullPath)
{
	return GetTexture(std::string(szFullPath));
}

void cTextureManager::AddTexture(const wchar_t* szFullPath, OUT LPDIRECT3DTEXTURE9 & texture, D3DXVECTOR2* imgInfo)
{
	/*char* szbuf = "fefefefef";
	std::string s(szbuf, szbuf + strlen(szbuf));
	std::wstring ws(sFullPath.begin(), sFullPath.end());*/
	D3DXIMAGE_INFO _info;
	D3DXGetImageInfoFromFile(szFullPath, &_info);
	imgInfo->x = _info.Width; imgInfo->y = _info.Height;
	if (FAILED(D3DXCreateTextureFromFileEx(g_pD3DDevice, szFullPath,
		_info.Width,_info.Height,
		1,0,
		D3DFMT_A8R8G8B8,D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT,
		D3DCOLOR_ARGB(0,255,255,255),NULL,NULL, &texture)))
	{
		
	}
}

void cTextureManager::Destroy()
{
	for each(auto p in m_mapTexture)
	{
		SAFE_RELEASE(p.second);
	}
	m_mapTexture.clear();
}
