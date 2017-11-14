#include "stdafx.h"
#include "cSpriteManager.h"


cSpriteManager::cSpriteManager()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
}


cSpriteManager::~cSpriteManager()
{

}

LPD3DXSPRITE cSpriteManager::GetDevice()
{
	return m_pSprite;
}

void cSpriteManager::BeginScene()
{
	//월드 매트릭스와 뷰행렬이 들어가야함
	m_pSprite->SetWorldViewLH(NULL, NULL);
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void cSpriteManager::Render(LPDIRECT3DTEXTURE9 texture, RECT * srcRect, D3DXVECTOR3 * scale, D3DXVECTOR3 * pos, DWORD alpha)
{
	D3DXCOLOR c = D3DCOLOR_ARGB(alpha, 255, 255, 255);
	m_pSprite->Draw(texture, srcRect, scale, pos, c);
}

void cSpriteManager::Destroy()
{
	m_pSprite->Release();
}
