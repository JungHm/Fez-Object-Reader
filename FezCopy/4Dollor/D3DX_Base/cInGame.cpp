#include "stdafx.h"
#include "cInGame.h"


cInGame::cInGame()
{
}


cInGame::~cInGame()
{
}

void cInGame::SetUp()
{
}

void cInGame::Destroy()
{
}

void cInGame::Update()
{
	if (GetAsyncKeyState(VK_LBUTTON)&0001)
	{
		g_Scene->ChangeScene("menu");
	}
}

void cInGame::Render()
{
}
