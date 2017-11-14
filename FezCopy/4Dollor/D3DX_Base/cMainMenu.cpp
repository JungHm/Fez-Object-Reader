#include "stdafx.h"
#include "cMainMenu.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cUtil.h"



cMainMenu::cMainMenu()
	: m_pGrid(NULL)
	, m_pCamera(NULL)
	, m_pD3DTexture(NULL)
{
}


cMainMenu::~cMainMenu()
{

}

void cMainMenu::SetUp()
{

	m_pGrid = new cGrid;
	m_pGrid->Setup("Grid", "field.png", 80, 160, 1.0f);


}

void cMainMenu::Destroy()
{
	SAFE_DELETE(m_pGrid);
	SAFE_RELEASE(m_pD3DTexture);
	XFile->Destroy();
	//m_pRootNode->Destroy();
}

void cMainMenu::Update()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0001)
	{
		g_Scene->ChangeScene("game");
	}
}

void cMainMenu::Render()
{
	//g_pSprite->BeginScene();
	//g_pSprite->Render(m_pD3DTexture, NULL, NULL, &D3DXVECTOR3(100, 100, 0), 255);
	//g_pSprite->End();

	if (m_pGrid)
		m_pGrid->Render();



}

void cMainMenu::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_ptMouse.x = LOWORD(lParam);
	m_ptMouse.y = HIWORD(lParam);
}

void cMainMenu::SetLight()
{
	D3DLIGHT9 light;

	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 vDir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	light.Direction = vDir;
	g_pD3DDevice->SetLight(0, &light);

	g_pD3DDevice->LightEnable(0, true);
}
