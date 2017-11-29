#pragma once
class FileStream;
#include "cGrid.h"
class cMainGame
{
private:
	FileStream* m_pFile;
	cGrid* m_pGrid;
	LPD3DXMESH	owlHead;
	LPD3DXMESH	owlBody;

	float angle;
public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

