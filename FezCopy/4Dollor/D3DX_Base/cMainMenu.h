#pragma once
#include "iScene.h"

class cGrid;
class cCamera;

class cMainMenu : public iScene
{
private:
	std::vector<ST_PC_VERTEXT>	m_vecVertex;
	cGrid*		m_pGrid;
	cCamera*	m_pCamera;

	LPDIRECT3DTEXTURE9		m_pD3DTexture;

private:
	POINT m_ptMouse;
public:
	cMainMenu();
	~cMainMenu();

	virtual void SetUp() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	void SetLight();

};

