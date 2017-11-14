#pragma once
#include "cMainMenu.h"
#include "cInGame.h"
class cMainGame
{
private:
	
public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

