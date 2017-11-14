#pragma once
#define g_pTextureManager cTextureManager::GetInstance()

class cTextureManager
{
private:
	SINGLETONE(cTextureManager);

	std::map<std::string, LPDIRECT3DTEXTURE9>	m_mapTexture;

public:
	LPDIRECT3DTEXTURE9 GetTexture(std::string sFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullPath);
	void AddTexture(const wchar_t* szFullPath, OUT LPDIRECT3DTEXTURE9& texture, D3DXVECTOR2* imgInfo);
	//void AddTexture(const wchar_t* szFullPath, OUT LPDIRECT3DTEXTURE9& texture);
	void Destroy();
};

