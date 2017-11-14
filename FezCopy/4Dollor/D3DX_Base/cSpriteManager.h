#pragma once
#define g_pSprite cSpriteManager::GetInstance()
#define g_pSpriteManager cSpriteManager::GetInstance()->GetDevice()

class cSpriteManager
{
	SINGLETONE(cSpriteManager);
private:
	LPD3DXSPRITE m_pSprite;
public:
	LPD3DXSPRITE GetDevice();
	void BeginScene();
	void Render(LPDIRECT3DTEXTURE9 texture, RECT* srcRect, D3DXVECTOR3* scale, D3DXVECTOR3* pos, DWORD alpha=255);
	void End() { m_pSprite->End();  }
	void Destroy();

};

