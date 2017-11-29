#include "stdafx.h"
#include "cMainGame.h"
#include "FileStream.h"



cMainGame::cMainGame()
{
	angle = 0.0f;
}


cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pGrid);
	owlHead->Release();
	owlBody->Release();
	g_pSprite->Destroy();
	g_pTextureManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	m_pGrid = new cGrid;
	m_pGrid->Setup("", "field2.png", 50, 50, 1.0f);

	m_pFile = new FileStream;
	m_pFile->LoadFromXml(L"big_owlao.xml");
	m_pFile->MakeMesh(&owlBody);
	m_pFile->LoadFromXml(L"big_owl_headao.xml");
	m_pFile->MakeMesh(&owlHead);
	g_pTextureManager->GetTexture("big_owl_headao.png");



	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
}


void cMainGame::Update()
{

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		angle += 0.1f;
	}
	g_pTimeManager->Update();

	g_pTimeManager->GetLastUpdateTime();
	g_Cam->Update();



}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(155, 155, 155),
		1.0f, 0);
	g_pD3DDevice->BeginScene();

	m_pGrid->Render();

	D3DXMATRIXA16 matS, matR; D3DXMatrixIdentity(&matS); D3DXMatrixIdentity(&matR);
	D3DXMATRIXA16 matWorld; D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matS, 8.0f, 8.0f, 8.0f); D3DXMatrixRotationY(&matR, angle);
	matWorld = matS*matR;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("big_owl_headao.png"));
	owlBody->DrawSubset(0);
	owlHead->DrawSubset(0);


	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}


void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_Cam->WndProc(hWnd, message, wParam, lParam);
}